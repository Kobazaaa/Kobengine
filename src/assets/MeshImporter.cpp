// -- Kobengine Includes --
#include "MeshImporter.h"

// -- Pompeii Includes --
#include "Renderer.h"
#include "Mesh.h"
#include "Material.h"

// -- Model Loading --
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

// -- Standard Library --
#include <iostream>
#include <unordered_map>

namespace
{
	//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//? ~~	  Import Context
	//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ImportContext
	{
		pompeii::Renderer& renderer;
		pompeii::MeshCreateInfo createInfo{};
		std::unordered_map<std::string, pompeii::TextureHandle> pathToTexture{};
	};

	glm::mat4 ConvertAssimpMatrix(const aiMatrix4x4& mat)
	{
		return glm::mat4(
			mat.a1, mat.b1, mat.c1, mat.d1,
			mat.a2, mat.b2, mat.c2, mat.d2,
			mat.a3, mat.b3, mat.c3, mat.d3,
			mat.a4, mat.b4, mat.c4, mat.d4
		);
	}

	pompeii::TextureHandle LoadMaterialTexture(ImportContext& ctx, const aiMaterial* pMaterial, aiTextureType type, VkFormat format)
	{
		if (pMaterial->GetTextureCount(type) == 0)
			return {};

		aiString texturePath;
		pMaterial->GetTexture(type, 0, &texturePath);
		const std::string fullPath = "textures/" + std::string(texturePath.C_Str());

		const auto it = ctx.pathToTexture.find(fullPath);
		if (it != ctx.pathToTexture.end())
			return it->second;

		const pompeii::TextureHandle handle = ctx.renderer.CreateTexture(pompeii::TextureCreateInfo
			{
				.path = fullPath,
				.format = format,
				.isHDR = false,
			});
		ctx.pathToTexture.emplace(fullPath, handle);
		return handle;
	}

	void ProcessMesh(ImportContext& ctx, const aiMesh* pMesh, const aiScene* pScene, const glm::mat4& transform)
	{
		pompeii::SubMesh subMesh{};
		subMesh.name = pMesh->mName.C_Str();
		subMesh.matrix = transform;

		auto& vertices = ctx.createInfo.vertices;
		auto& indices = ctx.createInfo.indices;

		// -- Process Vertices --
		subMesh.vertexOffset = static_cast<uint32_t>(vertices.size());
		for (uint32_t vIdx{}; vIdx < pMesh->mNumVertices; ++vIdx)
		{
			pompeii::Vertex vertex{};

			vertex.position = glm::vec3(pMesh->mVertices[vIdx].x,
				pMesh->mVertices[vIdx].y,
				pMesh->mVertices[vIdx].z);

			if (pMesh->HasNormals())
				vertex.normal = glm::vec3(pMesh->mNormals[vIdx].x,
					pMesh->mNormals[vIdx].y,
					pMesh->mNormals[vIdx].z);

			if (pMesh->mTextureCoords[0])
				vertex.texCoord = glm::vec2(pMesh->mTextureCoords[0][vIdx].x, pMesh->mTextureCoords[0][vIdx].y);
			else
				vertex.texCoord = glm::vec2(0.0f, 0.0f);

			vertex.color = glm::vec3(1.f, 1.f, 1.f);
			if (pMesh->HasVertexColors(vIdx))
			{
				const auto c = pMesh->mColors[vIdx];
				vertex.color = glm::vec3{ c->r, c->g, c->b };
			}

			if (pMesh->HasTangentsAndBitangents())
			{
				vertex.tangent = glm::vec3(pMesh->mTangents[vIdx].x,
					pMesh->mTangents[vIdx].y,
					pMesh->mTangents[vIdx].z);
				vertex.bitangent = glm::vec3(pMesh->mBitangents[vIdx].x,
					pMesh->mBitangents[vIdx].y,
					pMesh->mBitangents[vIdx].z);
			}
			vertices.push_back(vertex);
			subMesh.aabb.GrowToInclude(vertex.position);
			ctx.createInfo.aabb.GrowToInclude(subMesh.matrix * glm::vec4{ vertex.position, 1.f });
		}

		// -- Process Indices --
		subMesh.indexOffset = static_cast<uint32_t>(indices.size());
		for (uint32_t fIdx{}; fIdx < pMesh->mNumFaces; ++fIdx)
		{
			const aiFace& face = pMesh->mFaces[fIdx];
			for (uint32_t iIdx{}; iIdx < face.mNumIndices; ++iIdx)
				indices.push_back(face.mIndices[iIdx]);
		}
		subMesh.indexCount = static_cast<uint32_t>(indices.size()) - subMesh.indexOffset;

		// -- Process Material --
		const aiMaterial* pMaterial = pScene->mMaterials[pMesh->mMaterialIndex];
		pompeii::MaterialCreateInfo materialInfo{};
		materialInfo.albedo = LoadMaterialTexture(ctx, pMaterial, aiTextureType_DIFFUSE, VK_FORMAT_R8G8B8A8_SRGB);
		materialInfo.specular = LoadMaterialTexture(ctx, pMaterial, aiTextureType_SPECULAR, VK_FORMAT_R8G8B8A8_UNORM);
		materialInfo.shininess = LoadMaterialTexture(ctx, pMaterial, aiTextureType_SHININESS, VK_FORMAT_R8G8B8A8_UNORM);
		materialInfo.height = LoadMaterialTexture(ctx, pMaterial, aiTextureType_HEIGHT, VK_FORMAT_R8G8B8A8_UNORM);
		materialInfo.normal = LoadMaterialTexture(ctx, pMaterial, aiTextureType_NORMALS, VK_FORMAT_R8G8B8A8_UNORM);
		materialInfo.roughnessMap = LoadMaterialTexture(ctx, pMaterial, aiTextureType_DIFFUSE_ROUGHNESS, VK_FORMAT_R8G8B8A8_UNORM);
		materialInfo.metalnessMap = LoadMaterialTexture(ctx, pMaterial, aiTextureType_METALNESS, VK_FORMAT_R8G8B8A8_UNORM);
		materialInfo.opacity = LoadMaterialTexture(ctx, pMaterial, aiTextureType_OPACITY, VK_FORMAT_R8G8B8A8_UNORM);

		subMesh.material = ctx.renderer.CreateMaterial(materialInfo);
		ctx.createInfo.submeshes.push_back(subMesh);
	}

	void ProcessNode(ImportContext& ctx, const aiNode* pNode, const aiScene* pScene, const glm::mat4& transform)
	{
		const glm::mat4 nodeTransform = ConvertAssimpMatrix(pNode->mTransformation);
		const glm::mat4 totalTransform = transform * nodeTransform;

		for (uint32_t index{}; index < pNode->mNumMeshes; ++index)
		{
			const aiMesh* pMesh = pScene->mMeshes[pNode->mMeshes[index]];
			ProcessMesh(ctx, pMesh, pScene, totalTransform);
		}

		for (uint32_t cIdx{}; cIdx < pNode->mNumChildren; ++cIdx)
			ProcessNode(ctx, pNode->mChildren[cIdx], pScene, totalTransform);
	}
}

//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//? ~~	  Mesh Importer
//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
pompeii::MeshHandle kobengine::MeshImporter::Import(pompeii::Renderer& renderer, const std::string& path)
{
	Assimp::Importer importer;
	const aiScene* pScene =
		importer.ReadFile(path,
			aiProcess_Triangulate |
			aiProcess_OptimizeMeshes |
			aiProcess_CalcTangentSpace |
			aiProcess_ConvertToLeftHanded |
			aiProcess_JoinIdenticalVertices |
			aiProcess_SortByPType);

	if (!pScene || pScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !pScene->mRootNode)
	{
		std::cerr << "ASSIMP ERROR: " << importer.GetErrorString() << "\n";
		return {};
	}

	ImportContext ctx{ renderer };
	ProcessNode(ctx, pScene->mRootNode, pScene, glm::mat4(1.0f));

	return renderer.CreateMesh(ctx.createInfo);
}
