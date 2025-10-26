#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

// -- Kobengine Includes --
#include "Component.h"
#include "MeshFilter.h"

namespace kobengine
{
	//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//? ~~	  Model	
	//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	class MeshRenderer final : public Component
	{
	public:
		//--------------------------------------------------
		//    Constructor & Destructor
		//--------------------------------------------------
		explicit MeshRenderer(SceneObject& sceneObj, MeshFilter& filter);
		~MeshRenderer() override;

		MeshRenderer(const MeshRenderer& other) = delete;
		MeshRenderer(MeshRenderer&& other) noexcept = delete;
		MeshRenderer& operator=(const MeshRenderer& other) = delete;
		MeshRenderer& operator=(MeshRenderer&& other) noexcept = delete;

		//--------------------------------------------------
		//    Loop
		//--------------------------------------------------
		void Start() override;
		void OnInspectorDraw() override;

		//--------------------------------------------------
		//    Data
		//--------------------------------------------------
		MeshFilter* pMeshFilter{};
	};
}

#endif // MESH_RENDERER_H