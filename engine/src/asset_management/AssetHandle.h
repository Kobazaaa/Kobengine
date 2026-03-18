#ifndef KOBENGINE_ASSET_HANDLE_H
#define KOBENGINE_ASSET_HANDLE_H

// -- Standard Library --
#include <string>

// -- Kobengine Includes --
#include "AssetManager.h"

// -- Forward Declarations --
namespace kobengine
{
	class AssetManager;
}

namespace kobengine
{
	//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//? ~~    AssetHandle
	//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	template<typename AssetType>
	class AssetHandle final
	{
	public:
		//--------------------------------------------------
		//    Constructor & Destructor
		//--------------------------------------------------
		explicit AssetHandle() = default;
		explicit AssetHandle(const std::string& id, AssetManager* pManager)
			: m_AssetID(id)
			, m_pAssetManager(pManager)
		{}
		~AssetHandle() = default;

		AssetHandle(const AssetHandle& other) = default;
		AssetHandle(AssetHandle&& other) noexcept = default;
		AssetHandle& operator=(const AssetHandle& other) = default;
		AssetHandle& operator=(AssetHandle&& other) noexcept = default;

		//--------------------------------------------------
		//    Accessors & Mutators
		//--------------------------------------------------
		[[nodiscard]] AssetType* Get() const
		{
			if (!m_pAssetManager) return nullptr; // let user handle
			return m_pAssetManager->GetAsset<AssetType>(m_AssetID);
		}
		[[nodiscard]] bool IsValid()				const { return m_pAssetManager && m_pAssetManager->HasAsset<AssetType>(m_AssetID);}
		[[nodiscard]] const std::string& GetId()	const { return m_AssetID; }

		//--------------------------------------------------
		//    Operator Overloads
		//--------------------------------------------------
		AssetType* operator->() const { return Get(); }
		AssetType& operator*()	const { return *Get(); }
		operator bool()			const { return IsValid(); }

	private:
		std::string m_AssetID {};
		AssetManager* m_pAssetManager { nullptr };
	};
}

#endif // KOBENGINE_ASSET_HANDLE_H
