// -- Kobengine Includes --
#include "AssetHandle.h"
#include "AssetManager.h"

//--------------------------------------------------
//    Constructor & Destructor
//--------------------------------------------------
template <typename AssetType>
kobengine::AssetHandle<AssetType>::AssetHandle(const std::string& id, AssetManager* pManager)
	: m_AssetID(id)
	, m_pAssetManager(pManager)
{}

//--------------------------------------------------
//    Accessors & Mutators
//--------------------------------------------------
template <typename AssetType>
AssetType* kobengine::AssetHandle<AssetType>::Get() const
{
	if (!m_pAssetManager) return nullptr; // let user handle
	return m_pAssetManager->GetAsset<AssetType>(m_AssetID);
}

template <typename AssetType>
bool kobengine::AssetHandle<AssetType>::IsValid() const
{
	return m_pAssetManager && m_pAssetManager->HasAsset<AssetType>(m_AssetID);
}

template <typename AssetType>
const std::string& kobengine::AssetHandle<AssetType>::GetId() const
{
	return m_AssetID;
}


//--------------------------------------------------
//    Operator Overloads
//--------------------------------------------------
template <typename AssetType>
AssetType* kobengine::AssetHandle<AssetType>::operator->() const
{
	return Get();
}

template <typename AssetType>
AssetType& kobengine::AssetHandle<AssetType>::operator*() const
{
	return *Get();
}

template <typename AssetType>
kobengine::AssetHandle<AssetType>::operator bool() const
{
	return IsValid();
}
