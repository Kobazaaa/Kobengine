#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

// -- Standard Library --
#include <unordered_map>
#include <memory>
#include <string>

// -- Kobengine Includes --
#include "Mesh.h" 
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
		pompeii::Mesh* LoadMesh(const std::string& path);
		pompeii::Mesh* GetMesh(const std::string& path);
		void UnloadMesh(const pompeii::Mesh* pMesh);
		void UnloadAll();
		std::vector<pompeii::Mesh*> GetAllMeshes() const;

	private:
		std::unordered_map<std::string, std::unique_ptr<pompeii::Mesh>> m_vMeshRegistry{};
		std::shared_ptr<pompeii::Renderer> m_pRenderer{};
	};
}

#endif // ASSET_MANAGER_H
