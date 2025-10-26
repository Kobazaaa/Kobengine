// -- Kobengine Includes --
#include "Scene.h"

//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//? ~~	  Base Scene	
//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//--------------------------------------------------
//    Constructor & Destructor
//--------------------------------------------------
kobengine::Scene::Scene(std::string sceneName)
	: name(std::move(sceneName))
{}


//--------------------------------------------------
//    Adding & Removing SceneObjects
//--------------------------------------------------
kobengine::SceneObject& kobengine::Scene::AddEmpty(const std::string& sceneName)
{
	m_vPendingObjects.emplace_back(std::make_unique<SceneObject>(*this, sceneName));
	return *m_vPendingObjects.back();
}

//--------------------------------------------------
//    Loop
//--------------------------------------------------
void kobengine::Scene::Start() const
{
	for (auto& object : m_vObjects)
	{
		object->Start();
	}
}
void kobengine::Scene::Update()
{
	for (auto& object : m_vObjects)
	{
		if (!object->IsActive())
			continue;
		object->Update();
	}
	CleanupDeletedObjects();
	AddPendingObjects();
}

//--------------------------------------------------
//    Accessors
//--------------------------------------------------
std::vector<kobengine::SceneObject*> kobengine::Scene::GetObjectsByName(const std::string& objectName) const
{
	//todo Preferably get rid of string comparisons
	std::vector<SceneObject*> result{};
	for (auto& object : m_vObjects)
	{
		if (object->name == objectName)
			result.push_back(object.get());
	}
	for (auto& object : m_vPendingObjects)
	{
		if (object->name == objectName)
			result.push_back(object.get());
	}
	return result;
}
std::vector<kobengine::SceneObject*> kobengine::Scene::GetAllObjects() const
{
	std::vector<SceneObject*> result{};
	result.reserve(m_vObjects.size() + m_vPendingObjects.size());
	for (auto& object : m_vObjects)
		result.push_back(object.get());
	for (auto& object : m_vPendingObjects)
		result.push_back(object.get());
	return result;
}

const pompeii::AABB& kobengine::Scene::GetAABB() const
{
	return m_AABB;
}
void kobengine::Scene::GrowAABB(const pompeii::AABB& aabb)
{
	m_AABB.GrowToInclude(aabb);
}

void kobengine::Scene::CleanupDeletedObjects()
{
	std::erase_if(m_vObjects,
		[](const std::unique_ptr<SceneObject>& object)
		{
			return object->IsFlaggedForDestruction();
		});
}
void kobengine::Scene::AddPendingObjects()
{
	// separate for loops to ensure that all objects in m_vPendingObjects are in a valid state, since it's possible to query
	// m_vPendingObjects in the start function of SceneObjects (e.g. asking for all SO with tag or name).
	for (const auto& object : m_vPendingObjects)
		object->Start();
	for (auto& object : m_vPendingObjects)
		m_vObjects.push_back(std::move(object));
	m_vPendingObjects.clear();
}

