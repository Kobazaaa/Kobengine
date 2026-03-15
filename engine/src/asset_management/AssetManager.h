#ifndef KOBENGINE_ASSET_MANAGER_H
#define KOBENGINE_ASSET_MANAGER_H

// -- Standard Library --
#include <unordered_map>
#include <memory>
#include <string>
#include <typeindex>

// -- Kobengine Includes --
#include "Asset.h"

// -- Forward Declarations --
namespace kobengine
{
	template<typename AssetType>
	class AssetHandle;
}

namespace kobengine
{
	//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//? ~~	  Asset Manager
	//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	class AssetManager final
	{
	public:
		//--------------------------------------------------
		//    Constructor & Destructor
		//--------------------------------------------------
		explicit AssetManager() = default;
		~AssetManager();

		AssetManager(const AssetManager& other) = default;
		AssetManager(AssetManager&& other) noexcept = default;
		AssetManager& operator=(const AssetManager& other) = default;
		AssetManager& operator=(AssetManager&& other) noexcept = default;

		//--------------------------------------------------
		//    Functionality
		//--------------------------------------------------
		template<typename AssetType>
			requires std::derived_from<AssetType, Asset>
		AssetHandle<AssetType> LoadAsset(const std::string& assetID)
		{
			const auto typeIndex = std::type_index(typeid(AssetType));
			auto& allAssetsOfType = m_vAssets[typeIndex];

			// asset already exists
			if (allAssetsOfType.contains(assetID))
			{
				++allAssetsOfType[assetID].referenceCount;
				return AssetHandle<AssetType>(assetID, this);
			}

			// asset doesn't exist yet
			auto asset = std::make_unique<AssetType>(assetID);
			if (!asset->Load())
			{
				// loading failed! Return invalid asset handle and let user handle it
				return AssetHandle<AssetType>();
			}

			// loading succeeded, add to registry and return handle
			allAssetsOfType[assetID].pAsset = std::move(asset);
			allAssetsOfType[assetID].referenceCount = 1;

			return AssetHandle<AssetType>(assetID, this);
		}

		template<typename AssetType>
			requires std::derived_from<AssetType, Asset>
		bool UnloadAsset(const std::string& assetID)
		{
			const auto typeIndex = std::type_index(typeid(AssetType));
			const auto typeIt = m_vAssets.find(typeIndex);

			if (typeIt == m_vAssets.end()) // no stored assets of specified type, therefore can't unload asset of that type
				return false;

			auto& assetMap = typeIt->second;
			const auto  assetIt = assetMap.find(assetID);
			if (assetIt == assetMap.end()) // no asset if specified ID found in map, therefore can't unload asset of that ID
				return false;

			auto& [pAsset, referenceCount] = assetIt->second;
			pAsset->Unload();
			--referenceCount;
			assetMap.erase(assetID);

			return true;
		}

		void UnloadAllAssets();

		//--------------------------------------------------
		//    Accessors
		//--------------------------------------------------
		template<typename AssetType>
			requires std::derived_from<AssetType, Asset>
		AssetType* GetAsset(const std::string& assetID)
		{
			const auto typeIndex = std::type_index(typeid(AssetType));
			const auto typeIt = m_vAssets.find(typeIndex);

			if (typeIt == m_vAssets.end())
				return nullptr; // no stored assets of specified type, therefore can't get asset of that type

			auto& allAssetsOfType = typeIt->second;
			const auto assetIt = allAssetsOfType.find(assetID);

			// asset with id doesn't exist
			if (assetIt == allAssetsOfType.end())
				return nullptr; // let user handle it

			// asset does exist
			return static_cast<AssetType*>(assetIt->second.pAsset.get()); // static cast is safe because we only store assets of the correct type in each map
		}

		template<typename AssetType>
			requires std::derived_from<AssetType, Asset>
		bool HasAsset(const std::string& assetID)
		{
			const auto typeIndex = std::type_index(typeid(AssetType));
			const auto typeIt = m_vAssets.find(typeIndex);

			if (typeIt == m_vAssets.end())
				return false; // no stored assets of specified type, therefore can't get asset of that type

			const auto& allAssetsOfType = typeIt->second;
			return allAssetsOfType.contains(assetID);
		}

	private:
		struct AssetData
		{
			std::unique_ptr<Asset> pAsset {};
			int referenceCount {};
		};

		// Sort by type, then by ID to get to asset data
		std::unordered_map<std::type_index,	std::unordered_map<std::string, AssetData>> m_vAssets;
	};
}

#endif // KOBENGINE_ASSET_MANAGER_H
