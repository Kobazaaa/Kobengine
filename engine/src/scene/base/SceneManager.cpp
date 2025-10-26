// -- Kobengine Includes --
#include "SceneManager.h"

// -- Standard Library --
#include <algorithm>

//--------------------------------------------------
//    Constructor & Destructor
//--------------------------------------------------
kobengine::Scene& kobengine::SceneManager::CreateScene(const std::string& name)
{
	// Create new scene with name, if it already exists, return existing scene
	const auto it = std::ranges::find_if(m_vScenes, [name](const std::unique_ptr<Scene>& pScene) { return pScene->name == name; });
	if (it == m_vScenes.end())
	{
		m_vScenes.push_back(std::make_unique<Scene>(name));
		if (m_vScenes.size() == 1)
			m_pActiveScene = m_vScenes[0].get();
		return *m_vScenes.back();
	}
	return **it;
}


//--------------------------------------------------
//    Accessors & Mutators
//--------------------------------------------------
kobengine::Scene* kobengine::SceneManager::GetScene(uint32_t index) const
{
	if (index < 0u || index >= static_cast<uint32_t>(m_vScenes.size()))
		return nullptr;
	return m_vScenes[index].get();
}
kobengine::Scene* kobengine::SceneManager::GetScene(const std::string& name) const
{
	for (auto& scene : m_vScenes)
		if (scene->name == name)
			return scene.get();
	return nullptr;
}

kobengine::Scene& kobengine::SceneManager::GetActiveScene() const { return *m_pActiveScene; }
void kobengine::SceneManager::SetActiveScene(Scene& scene)
{
	m_pActiveScene = &scene;
	Start();
}
void kobengine::SceneManager::SetActiveScene(const std::string& name) { if (const auto pScene = GetScene(name)) SetActiveScene(*pScene); }


//--------------------------------------------------
//    Loop
//--------------------------------------------------
void kobengine::SceneManager::Start()		const { m_pActiveScene->Start(); }
void kobengine::SceneManager::Update()		const { m_pActiveScene->Update(); }
