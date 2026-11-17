// -- Kobengine Includes --
#include "AssetManager.h"
#include "MeshImporter.h"

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
pompeii::MeshHandle kobengine::AssetManager::LoadMesh(const std::string& path)
{
	const auto existing = m_MeshRegistry.find(path);
	if (existing != m_MeshRegistry.end())
		return existing->second;

	const pompeii::MeshHandle handle = MeshImporter::Import(*m_pRenderer, path);
	m_MeshRegistry[path] = handle;
	return handle;
}
pompeii::MeshHandle kobengine::AssetManager::GetMesh(const std::string& path) const
{
	const auto existing = m_MeshRegistry.find(path);
	if (existing != m_MeshRegistry.end())
		return existing->second;
	return {};
}

void kobengine::AssetManager::UnloadMesh(pompeii::MeshHandle handle)
{
	const auto it = std::ranges::find_if(
			m_MeshRegistry,
			[handle](const std::pair<const std::string, pompeii::MeshHandle>& pair)
			{
				return pair.second == handle;
			});
	if (it != m_MeshRegistry.end())
	{
		m_pRenderer->DestroyMesh(handle);
		m_MeshRegistry.erase(it);
	}
}
void kobengine::AssetManager::UnloadAll()
{
	for (const pompeii::MeshHandle handle : m_MeshRegistry | std::views::values)
		m_pRenderer->DestroyMesh(handle);
	m_MeshRegistry.clear();
}
std::vector<pompeii::MeshHandle> kobengine::AssetManager::GetAllMeshes() const
{
	std::vector<pompeii::MeshHandle> res{};
	res.reserve(m_MeshRegistry.size());
	for (const pompeii::MeshHandle handle : m_MeshRegistry | std::views::values)
		res.emplace_back(handle);
	return res;
}
