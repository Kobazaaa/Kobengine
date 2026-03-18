// -- Kobengine Includes --
#include "Mesh.h"
#include "Debug.h"

// -- Standard Library --
#include <iostream>

// -- Assimp Includes --
#include "assimp/postprocess.h"
#include "assimp/Importer.hpp"


//--------------------------------------------------
//    Constructor & Destructor
//--------------------------------------------------
kobengine::Mesh::Mesh(const std::string& id, const std::string& path)
	: Asset(id)
	, m_FilePath{path}
{}

//--------------------------------------------------
//    Functionality
//--------------------------------------------------
bool kobengine::Mesh::DoLoad()
{
	if (m_FilePath.empty())
	{
		Debug::LogError("Failed to load mesh from an empty path!");
		return false;
	}

	Assimp::Importer importer;
	const aiScene* pScene =
		importer.ReadFile(m_FilePath,
			aiProcess_Triangulate |
			aiProcess_OptimizeMeshes |
			aiProcess_CalcTangentSpace |
			aiProcess_ConvertToLeftHanded |
			aiProcess_JoinIdenticalVertices |
			aiProcess_SortByPType);

	if (!pScene || pScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !pScene->mRootNode)
	{
		Debug::LogError("Failed to load mesh from path: " + m_FilePath);
		return false;
	}

	ProcessNode(pScene->mRootNode, pScene);
	return true;
}

bool kobengine::Mesh::DoUnload()
{
	m_vSubMeshes.clear();
	m_vVertices.clear();
	m_vIndices.clear();
	m_FilePath.clear();
	return true;
}


//--------------------------------------------------
//    Helpers
//--------------------------------------------------
void kobengine::Mesh::ProcessNode(const aiNode* pNode, const aiScene* pScene, const glm::mat4& transform)
{
	const glm::mat4 nodeTransform = ConvertAssimpMatrix(pNode->mTransformation);
	const glm::mat4 totalTransform = transform * nodeTransform;

	for (uint32_t index{}; index < pNode->mNumMeshes; ++index)
	{
		aiMesh* pMesh = pScene->mMeshes[pNode->mMeshes[index]];
		ProcessMesh(pMesh, totalTransform);
	}

	for (uint32_t cIdx{}; cIdx < pNode->mNumChildren; ++cIdx)
		ProcessNode(pNode->mChildren[cIdx], pScene, totalTransform);
}

void kobengine::Mesh::ProcessMesh(const aiMesh* pMesh, glm::mat4 transform)
{
	auto& lastSubMesh = m_vSubMeshes.emplace_back();
	lastSubMesh.name = pMesh->mName.C_Str();
	lastSubMesh.matrix = transform;

	// -- Process Vertices --
	lastSubMesh.vertexOffset = static_cast<uint32_t>(m_vVertices.size());
	for (uint32_t vIdx{}; vIdx < pMesh->mNumVertices; ++vIdx)
	{
		Vertex vertex{};

		vertex.position = glm::vec3(pMesh->mVertices[vIdx].x,
			pMesh->mVertices[vIdx].y,
			pMesh->mVertices[vIdx].z);

		if (pMesh->HasNormals())
			vertex.normal = glm::vec3(pMesh->mNormals[vIdx].x,
				pMesh->mNormals[vIdx].y,
				pMesh->mNormals[vIdx].z);

		if (pMesh->mTextureCoords[0]) vertex.texcoord = glm::vec2(pMesh->mTextureCoords[0][vIdx].x, pMesh->mTextureCoords[0][vIdx].y);
		else vertex.texcoord = glm::vec2(0.0f, 0.0f);

		vertex.color = glm::vec3(1.f, 1.f, 1.f);
		if (pMesh->HasVertexColors(vIdx))
		{
			auto c = pMesh->mColors[vIdx];
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

		m_vVertices.push_back(vertex);

		// -- Process Indices --
		lastSubMesh.indexOffset = static_cast<uint32_t>(m_vIndices.size());
		for (uint32_t fIdx{}; fIdx < pMesh->mNumFaces; ++fIdx)
		{
			aiFace face = pMesh->mFaces[fIdx];
			for (uint32_t iIdx{}; iIdx < face.mNumIndices; ++iIdx)
				m_vIndices.push_back(face.mIndices[iIdx]);
		}
		lastSubMesh.indexCount = static_cast<uint32_t>(m_vIndices.size()) - lastSubMesh.indexOffset;
	}
}

glm::mat4 kobengine::Mesh::ConvertAssimpMatrix(const aiMatrix4x4& mat)
{
	return glm::mat4(
		mat.a1, mat.b1, mat.c1, mat.d1,
		mat.a2, mat.b2, mat.c2, mat.d2,
		mat.a3, mat.b3, mat.c3, mat.d3,
		mat.a4, mat.b4, mat.c4, mat.d4
	);
}
