#ifndef MESH_FILTER_H
#define MESH_FILTER_H

// -- Kobengine Includes --
#include "AssetHandle.h"
#include "Component.h"

// -- Forward Declarations --
namespace kobengine
{
	class Mesh;
}

namespace kobengine
{
	//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//? ~~	  MeshFilter
	//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	class MeshFilter final : public Component
	{
	public:
		//--------------------------------------------------
		//    Constructor & Destructor
		//--------------------------------------------------
		explicit MeshFilter(SceneObject& sceneObj);
		~MeshFilter() override;

		MeshFilter(const MeshFilter& other) = delete;
		MeshFilter(MeshFilter&& other) noexcept = delete;
		MeshFilter& operator=(const MeshFilter& other) = delete;
		MeshFilter& operator=(MeshFilter&& other) noexcept = delete;

		//--------------------------------------------------
		//    Loop
		//--------------------------------------------------
		void Initialize() override;

		//--------------------------------------------------
		//    Data
		//--------------------------------------------------
		AssetHandle<Mesh>* pMesh{};
	};
}

#endif // MESH_FILTER_H