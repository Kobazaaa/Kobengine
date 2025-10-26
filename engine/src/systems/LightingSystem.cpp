// -- Pompeii Includes --
#include "LightingSystem.h"
#include "LightComponent.h"

// -- Standard Library --
#include <iterator>

#include "Scene.h"
#include "SceneObject.h"

//--------------------------------------------------
//    Lights
//--------------------------------------------------
void kobengine::LightingSystem::RegisterLight(LightComponent& light)
{
	auto it = std::ranges::find(m_vRegisteredLights, &light);
	if (it != m_vRegisteredLights.end())
		return;
	it = std::ranges::find(m_vPendingLights, &light);
	if (it != m_vPendingLights.end())
		return;
	m_UpdateLights = true;

	light.lightData.CalculateLightMatrices(light.GetSceneObject().GetScene().GetAABB());
	light.lightData.CreateDepthImage(m_pRenderer->GetContext(), 4096);

	m_vPendingLights.emplace_back(&light);
}
void kobengine::LightingSystem::UnregisterLight(LightComponent& light)
{
	m_UpdateLights = true;

	std::erase_if(m_vRegisteredLights, [&](const LightComponent* pLight)
	{
		if (pLight == &light)
		{
			m_pRenderer->GetContext().device.WaitIdle();
			light.lightData.DestroyDepthMap(m_pRenderer->GetContext());
		}
		return pLight == &light;
	});
	std::erase_if(m_vPendingLights, [&](const LightComponent* pLight)
	{
		if (pLight == &light)
		{
			m_pRenderer->GetContext().device.WaitIdle();
			light.lightData.DestroyDepthMap(m_pRenderer->GetContext());
		}
		return pLight == &light;
	});
}

void kobengine::LightingSystem::UpdateLight(LightComponent&)
{
	m_UpdateLights = true;
}

//--------------------------------------------------
//    Interface
//--------------------------------------------------
void kobengine::LightingSystem::Update()
{
	for (LightComponent* l : m_vRegisteredLights)
	{
		m_pRenderer->SubmitLightItem(pompeii::LightItem
			{
				.light = &l->lightData
			});
	}
	UpdateData();
}
void kobengine::LightingSystem::BeginFrame()
{
	AddPendingObjects();
}
void kobengine::LightingSystem::EndFrame()
{
}


void kobengine::LightingSystem::SetRenderer(const std::shared_ptr<pompeii::Renderer>& renderer)
{
	m_pRenderer = renderer;
}
pompeii::Renderer* kobengine::LightingSystem::GetRenderer() const
{
	return m_pRenderer.get();
}


//--------------------------------------------------
//    Helpers
//--------------------------------------------------
void kobengine::LightingSystem::AddPendingObjects()
{
	if (!m_vPendingLights.empty())
	{
		for (auto& pendingLight : m_vPendingLights)
			m_vRegisteredLights.emplace_back(pendingLight);
		m_vPendingLights.clear();
	}
}
void kobengine::LightingSystem::UpdateData()
{
	if (m_UpdateLights)
	{
		m_UpdateLights = false;

		std::vector<pompeii::Light*> newLights{};
		newLights.reserve(m_vRegisteredLights.size());
		for (auto& registeredLight : m_vRegisteredLights)
			newLights.push_back(&registeredLight->lightData);
		m_pRenderer->UpdateLights(newLights);
	}
}