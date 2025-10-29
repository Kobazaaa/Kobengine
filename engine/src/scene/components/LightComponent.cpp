// -- Kobengine Includes --
#include "LightComponent.h"
#include "ServiceLocator.h"
#include "LightingSystem.h"
#include "Scene.h"

//--------------------------------------------------
//    Constructor & Destructor
//--------------------------------------------------
kobengine::LightComponent::LightComponent(SceneObject& parent, const glm::vec3& dirPos, const glm::vec3& col, float luxLumen, pompeii::LightType type)
	: Component(parent, "LightComponent")
	, lightData
	{
		.dirPos = dirPos,
		.type = type,
		.color = col,
		.luxLumen = luxLumen,
		.viewMatrices = {},
		.projMatrix = {}
	}
{
	if (lightData.type == pompeii::LightType::Point)
		GetTransform().SetPosition(lightData.dirPos);
	lightData.CalculateLightMatrices(GetSceneObject().GetScene().GetAABB());
	ServiceLocator::Get<LightingSystem>().RegisterLight(*this);
}
kobengine::LightComponent::~LightComponent()
{
	ServiceLocator::Get<LightingSystem>().UnregisterLight(*this);
}


//--------------------------------------------------
//    Loop
//--------------------------------------------------
void kobengine::LightComponent::Start()
{
	ServiceLocator::Get<LightingSystem>().UpdateLight(*this);
}
void kobengine::LightComponent::Update()
{
}

