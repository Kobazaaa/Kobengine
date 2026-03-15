#ifndef KOBENGINE_ASSET_HANDLE_H
#define KOBENGINE_ASSET_HANDLE_H

// -- Standard Library --
#include <string>

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
		explicit AssetHandle(const std::string& id, AssetManager* pManager);
		~AssetHandle() = default;

		AssetHandle(const AssetHandle& other) = default;
		AssetHandle(AssetHandle&& other) noexcept = default;
		AssetHandle& operator=(const AssetHandle& other) = default;
		AssetHandle& operator=(AssetHandle&& other) noexcept = default;

		//--------------------------------------------------
		//    Accessors & Mutators
		//--------------------------------------------------
		[[nodiscard]] AssetType* Get() const;
		[[nodiscard]] bool IsValid() const;
		[[nodiscard]] const std::string& GetId() const;

		//--------------------------------------------------
		//    Operator Overloads
		//--------------------------------------------------
		AssetType* operator->() const;
		AssetType& operator*() const;
		operator bool() const;

	private:
		std::string m_AssetID {};
		AssetManager* m_pAssetManager { nullptr };
	};
}

#endif // KOBENGINE_ASSET_HANDLE_H
