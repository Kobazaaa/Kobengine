#ifndef KOBENGINE_ASSET_H
#define KOBENGINE_ASSET_H

// -- Standard Library --
#include <string>

namespace kobengine
{
	//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//? ~~    Asset
	//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	class Asset
	{
	public:
		//--------------------------------------------------
		//    Constructor & Destructor
		//--------------------------------------------------
		explicit Asset(const std::string& id) : m_AssetID(id) {}
		virtual ~Asset() = default;

		Asset(const Asset& other) = default;
		Asset(Asset&& other) noexcept = default;
		Asset& operator=(const Asset& other) = default;
		Asset& operator=(Asset&& other) noexcept = default;

		//--------------------------------------------------
		//    Functionality
		//--------------------------------------------------
		bool Load()
		{
			m_Loaded = DoLoad();
			return m_Loaded;
		}

		void Unload()
		{
			DoUnload();
		}

		//--------------------------------------------------
		//    Accessors & Mutators
		//--------------------------------------------------
		[[nodiscard]] const std::string& GetID() const { return m_AssetID; }
		[[nodiscard]] bool IsLoaded() const { return m_Loaded; }

	protected:
		virtual bool DoLoad() = 0;
		virtual bool DoUnload() = 0;

	private:
		std::string m_AssetID {};
		bool m_Loaded { false };
	};
}

#endif // KOBENGINE_ASSET_H
