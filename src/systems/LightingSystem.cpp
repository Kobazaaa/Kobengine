// -- Pompeii Includes --
#include "LightingSystem.h"
#include "LightComponent.h"

// -- Standard Library --
#include <iterator>

#include "Scene.h"
#include "SceneObject.h"

namespace
{
	pompeii::LightCreateInfo BuildCreateInfo(const kobengine::LightComponent& light)
	{
		return pompeii::LightCreateInfo
		{
			.type = light.type,
			.dirPos = light.dirPos,
			.color = light.color,
			.luxLumen = light.luxLumen,
			.shadowMapSize = 4096,
			.sceneAABB = light.GetSceneObject().GetScene().GetAABB(),
		};
	}
}

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

	light.lightHandle = m_pRenderer->CreateLight(BuildCreateInfo(light));

	m_vPendingLights.emplace_back(&light);
}
void kobengine::LightingSystem::UnregisterLight(LightComponent& light)
{
	std::erase_if(m_vRegisteredLights, [&](const LightComponent* pLight)
	{
		if (pLight == &light)
			m_pRenderer->DestroyLight(light.lightHandle);
		return pLight == &light;
	});
	std::erase_if(m_vPendingLights, [&](const LightComponent* pLight)
	{
		if (pLight == &light)
			m_pRenderer->DestroyLight(light.lightHandle);
		return pLight == &light;
	});
}

void kobengine::LightingSystem::UpdateLight(LightComponent& light)
{
	m_pRenderer->UpdateLight(light.lightHandle, BuildCreateInfo(light));
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
				.light = l->lightHandle
			});
	}
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
