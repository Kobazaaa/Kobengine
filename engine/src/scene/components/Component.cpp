// -- Pompeii Includes --
#include "Component.h"
#include "SceneObject.h"
kobengine::Component::Component(SceneObject& sceneObj, const std::string& name) : name{ name }, m_pSceneObj{ &sceneObj } {}
void kobengine::Component::Destroy()									{ m_DeletionFlag = true; }
bool kobengine::Component::IsFlaggedForDestruction()			const	{ return m_DeletionFlag; }
kobengine::SceneObject& kobengine::Component::GetSceneObject()	const	{ return *m_pSceneObj; }
kobengine::Transform& kobengine::Component::GetTransform()		const	{ return *m_pSceneObj->transform; }
