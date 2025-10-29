// -- Kobengine Includes --
#include "MeshFilter.h"
#include "AssetManager.h"
#include "ServiceLocator.h"

//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//? ~~	  MeshFilter	
//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//--------------------------------------------------
//    Constructor & Destructor
//--------------------------------------------------
kobengine::MeshFilter::MeshFilter(SceneObject& sceneObj)
	: Component(sceneObj, "MeshFilter")
{}
kobengine::MeshFilter::~MeshFilter()
{
	ServiceLocator::Get<AssetManager>().UnloadMesh(pMesh);
}


//--------------------------------------------------
//    Loop
//--------------------------------------------------
void kobengine::MeshFilter::Start()
{
}
