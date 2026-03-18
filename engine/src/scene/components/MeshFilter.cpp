// -- Kobengine Includes --
#include "MeshFilter.h"
#include "AssetManager.h"
#include "Mesh.h"

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
	if (pMesh) pMesh->Get()->Unload();
}


//--------------------------------------------------
//    Loop
//--------------------------------------------------
void kobengine::MeshFilter::Initialize()
{
}
