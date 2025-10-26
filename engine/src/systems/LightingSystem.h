#ifndef LIGHTING_SYSTEM_H
#define LIGHTING_SYSTEM_H

// -- Standard Library --
#include <vector>
#include <memory>

// -- Kobengine Includes --
#include "ISystem.h"
#include "Renderer.h"

// -- Forward Declarations --
namespace kobengine
{
	class LightComponent;
}

namespace kobengine
{
	//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//? ~~	  Lighting System	
	//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	class LightingSystem final : public ISystem
	{
	public:
		//--------------------------------------------------
		//    Lights
		//--------------------------------------------------
		void RegisterLight(LightComponent& light);
		void UnregisterLight(LightComponent& light);
		void UpdateLight(LightComponent& light);

		//--------------------------------------------------
		//    Interface
		//--------------------------------------------------
		void SetRenderer(const std::shared_ptr<pompeii::Renderer>& renderer);
		pompeii::Renderer* GetRenderer() const;
		void BeginFrame() override;
		void Update() override;
		void EndFrame() override;

	private:
		std::vector<LightComponent*> m_vPendingLights{};
		std::vector<LightComponent*> m_vRegisteredLights{};
		std::shared_ptr<pompeii::Renderer> m_pRenderer{};
		bool m_UpdateLights{};


		//--------------------------------------------------
		//    Helpers
		//--------------------------------------------------
		void AddPendingObjects();
		void UpdateData();
	};
}

#endif // RENDER_SYSTEM_H
