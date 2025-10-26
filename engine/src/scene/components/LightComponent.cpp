// -- Kobengine Includes --
#include "LightComponent.h"
#include "ServiceLocator.h"

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
void kobengine::LightComponent::OnInspectorDraw()
{
	ImGui::Text("Type"); ImGui::SameLine();
	if (ImGui::Combo("##Type", reinterpret_cast<int*>(&lightData.type), "Directional\0Point"))
	{
		ServiceLocator::Get<LightingSystem>().UpdateLight(*this);
	}

	ImGui::Text("Intensity"); ImGui::SameLine();
	if (ImGui::InputFloat("##Intensity", &lightData.luxLumen))
		ServiceLocator::Get<LightingSystem>().UpdateLight(*this);
	ImGui::Text("Color"); ImGui::SameLine();
	if (ImGui::ColorEdit3("##Color", &lightData.color.r))
		ServiceLocator::Get<LightingSystem>().UpdateLight(*this);

	if (ImGui::Button("Recalculate Matrices"))
		lightData.CalculateLightMatrices(GetSceneObject().GetScene().GetAABB());
}

