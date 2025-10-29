// -- Standard Library --
#include <string>

// -- Kobengine Includes --
#include "SceneObject.h"

//--------------------------------------------------
//    Constructors and Destructors
//--------------------------------------------------
kobengine::SceneObject::SceneObject(Scene& scene, std::string name)
	: name(std::move(name))
	, m_pScene(&scene)
{}

//--------------------------------------------------
//    Loop
//--------------------------------------------------
void kobengine::SceneObject::Start() const
{
	for (const auto& component : m_vComponents)
		if (component->isActive)
			component->Start();
}
void kobengine::SceneObject::Update() const
{
	for (const auto& component : m_vComponents)
		if (component->isActive)
			component->Update();
}

//--------------------------------------------------
//    Data
//--------------------------------------------------
kobengine::Scene& kobengine::SceneObject::GetScene() const
{
	return *m_pScene;
}

//--------------------------------------------------
//    Flags
//--------------------------------------------------
bool kobengine::SceneObject::IsFlaggedForDestruction() const
{
	return m_DeletionFlag;
}
void kobengine::SceneObject::Destroy()
{
	m_DeletionFlag = true;
	for (const auto& child : transform->GetAllChildren())
		child->GetSceneObject()->Destroy();
}

bool kobengine::SceneObject::IsActive() const
{
	return m_IsActive;
}
void kobengine::SceneObject::SetActive(bool active)
{
	m_IsActive = active;
	for (auto& child : transform->GetAllChildren())
		child->GetSceneObject()->SetActive(active);
}


//--------------------------------------------------
//    Deletion
//--------------------------------------------------

// -- Component --
void kobengine::SceneObject::CleanupDeletedComponents()
{
	std::erase_if(m_vComponents,
	              [](const std::unique_ptr<Component>& component)
	              {
		              return component->IsFlaggedForDestruction();
	              });
}

