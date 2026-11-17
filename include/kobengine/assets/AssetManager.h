#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

// -- Standard Library --
#include <unordered_map>
#include <memory>
#include <string>
#include <vector>

// -- Kobengine Includes --
#include "Handle.h"
#include "Renderer.h"

namespace kobengine
{
	//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//? ~~	  Asset Manager
	//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	class AssetManager final
	{
	public:
		//--------------------------------------------------
		//    Renderer
		//--------------------------------------------------
		void SetRenderer(const std::shared_ptr<pompeii::Renderer>& renderer);
		pompeii::Renderer* GetRenderer() const;

		//--------------------------------------------------
		//    Assets
		//--------------------------------------------------
		pompeii::MeshHandle LoadMesh(const std::string& path);
		pompeii::MeshHandle GetMesh(const std::string& path) const;
		void UnloadMesh(pompeii::MeshHandle handle);
		void UnloadAll();
		std::vector<pompeii::MeshHandle> GetAllMeshes() const;

	private:
		std::unordered_map<std::string, pompeii::MeshHandle> m_MeshRegistry{};
		std::shared_ptr<pompeii::Renderer> m_pRenderer{};
	};
}

#endif // ASSET_MANAGER_H
