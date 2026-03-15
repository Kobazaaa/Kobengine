// -- Standard Library --
#include <ranges>

// -- Kobengine Includes --
#include "AssetManager.h"


//--------------------------------------------------
//    Constructor & Destructor
//--------------------------------------------------
kobengine::AssetManager::~AssetManager()
{
	UnloadAllAssets();
}

//--------------------------------------------------
//    Functionality
//--------------------------------------------------
void kobengine::AssetManager::UnloadAllAssets()
{
	for (auto& idAssetMap : m_vAssets | std::views::values)
	{
		for (auto& [pAsset, referenceCount] : idAssetMap | std::views::values)
		{
			pAsset->Unload();
		}
		idAssetMap.clear();
	}
	m_vAssets.clear();
}
