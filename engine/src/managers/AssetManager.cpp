// -- Kobengine Includes --
#include "AssetManager.h"

// -- Standard Library --
#include <ranges>

//--------------------------------------------------
//    Renderer
//--------------------------------------------------
void kobengine::AssetManager::SetRenderer(const std::shared_ptr<pompeii::Renderer>& renderer)
{
	m_pRenderer = renderer;
}
pompeii::Renderer* kobengine::AssetManager::GetRenderer() const
{
	return m_pRenderer.get();
}

//--------------------------------------------------
//    Assets
//--------------------------------------------------
pompeii::Mesh* kobengine::AssetManager::LoadMesh(const std::string& path)
{
	if (!m_vMeshRegistry.contains(path))
	{
		m_vMeshRegistry[path] = std::make_unique<pompeii::Mesh>(path);
		m_vMeshRegistry[path]->AllocateResources(m_pRenderer->GetContext());
	}
	return GetMesh(path);
}
pompeii::Mesh* kobengine::AssetManager::GetMesh(const std::string& path)
{
	if (m_vMeshRegistry.contains(path))
		return m_vMeshRegistry[path].get();
	return nullptr;
}

void kobengine::AssetManager::UnloadMesh(const pompeii::Mesh* pMesh)
{
	auto it = std::ranges::find_if(
			m_vMeshRegistry,
			[pMesh](const std::pair<const std::string, std::unique_ptr<pompeii::Mesh>>& pair)
			{
				return pMesh == pair.second.get();
			});
	if (it != m_vMeshRegistry.end())
	{
		m_pRenderer->GetContext().device.WaitIdle();
		it->second->Destroy(m_pRenderer->GetContext());
		m_vMeshRegistry.erase(it);
	}
}
void kobengine::AssetManager::UnloadAll()
{
	m_pRenderer->GetContext().device.WaitIdle();
	for (auto& mesh : m_vMeshRegistry | std::views::values)
		mesh->Destroy(m_pRenderer->GetContext());
	m_vMeshRegistry.clear();
}
std::vector<pompeii::Mesh*> kobengine::AssetManager::GetAllMeshes() const
{
	std::vector<pompeii::Mesh*> res(m_vMeshRegistry.size());
	for (const auto& val : m_vMeshRegistry | std::views::values)
		res.emplace_back(val.get());
	return res;
}
