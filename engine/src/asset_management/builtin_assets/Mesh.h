#ifndef KOBENGINE_MESH_H
#define KOBENGINE_MESH_H

// -- Standard Library --
#include <vector>

// -- Kobengine Includes --
#include "Asset.h"

// -- Math Includes --
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_FORCE_LEFT_HANDED
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// -- Forward Declaration --
#include "assimp/matrix4x4.h"
#include "assimp/scene.h"

namespace kobengine
{
	//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//? ~~    Vertex
	//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 tangent;
		glm::vec3 bitangent;
		glm::vec2 texcoord;
		glm::vec3 color;
	};

	//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//? ~~    Mesh
	//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	class Mesh : public Asset
	{
	public:
		//--------------------------------------------------
		//    Constructor & Destructor
		//--------------------------------------------------
		explicit Mesh(const std::string& id, const std::string& path);
		~Mesh() override = default;

		Mesh(const Mesh& other) = default;
		Mesh(Mesh&& other) noexcept = default;
		Mesh& operator=(const Mesh& other) = default;
		Mesh& operator=(Mesh&& other) noexcept = default;

		//--------------------------------------------------
		//    Functionality
		//--------------------------------------------------

		//--------------------------------------------------
		//    Accessors & Mutators
		//--------------------------------------------------

	protected:
		bool DoLoad() override;
		bool DoUnload() override;

	private:
		//--------------------------------------------------
		//    Helpers
		//--------------------------------------------------
		void ProcessNode(const aiNode* pNode, const aiScene* pScene, const glm::mat4& transform = glm::mat4(1.0f));
		void ProcessMesh(const aiMesh* pMesh, glm::mat4 transform);

		static glm::mat4 ConvertAssimpMatrix(const aiMatrix4x4& mat);

		//--------------------------------------------------
		//    CPU Data
		//--------------------------------------------------
		std::string m_FilePath{};
		struct SubMesh
		{
			uint32_t vertexOffset{};
			uint32_t indexOffset{};
			uint32_t indexCount{};

			glm::mat4 matrix{};

			std::string name{};
		};
		std::vector<SubMesh> m_vSubMeshes{};
		std::vector<Vertex> m_vVertices{};
		std::vector<uint32_t> m_vIndices{};

		//--------------------------------------------------
		//    GPU Data
		//--------------------------------------------------

	};
}

#endif // KOBENGINE_MESH_H
