// -- Kobengine Includes --
#include "MeshRenderer.h"
#include "ServiceLocator.h"
#include "RenderSystem.h"
#include "Scene.h"

//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//? ~~	  Model	
//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//--------------------------------------------------
//    Constructor & Destructor
//--------------------------------------------------
kobengine::MeshRenderer::MeshRenderer(SceneObject& sceneObj, MeshFilter& filter)
	: Component(sceneObj, "MeshRenderer")
{
	pMeshFilter = &filter;
	ServiceLocator::Get<RenderSystem>().RegisterMeshRenderer(*this);
	if (const pompeii::Mesh* pMesh = ServiceLocator::Get<RenderSystem>().GetRenderer()->TryGetMesh(pMeshFilter->meshHandle))
		GetSceneObject().GetScene().GrowAABB(pMesh->aabb);
}
kobengine::MeshRenderer::~MeshRenderer()
{
	ServiceLocator::Get<RenderSystem>().UnregisterMeshRenderer(*this);
}


//--------------------------------------------------
//    Loop
//--------------------------------------------------
void kobengine::MeshRenderer::Initialize()
{
}
