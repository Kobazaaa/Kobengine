#ifndef GENERAL_LIGHT_H
#define GENERAL_LIGHT_H

// -- Math Includes --
#include "glm/glm.hpp"

// -- Kobengine Includes --
#include "Component.h"
#include "Handle.h"
#include "Light.h"

namespace kobengine
{
	//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//? ~~	  Light Component
	//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	class LightComponent final : public Component
	{
	public:
		//--------------------------------------------------
		//    Constructor & Destructor
		//--------------------------------------------------
		LightComponent(SceneObject& parent, const glm::vec3& dirPos, const glm::vec3& col, float luxLumen, pompeii::LightType type);
		~LightComponent() override;

		LightComponent(const LightComponent& other) = delete;
		LightComponent(LightComponent&& other) noexcept = delete;
		LightComponent& operator=(const LightComponent& other) = delete;
		LightComponent& operator=(LightComponent&& other) noexcept = delete;


		//--------------------------------------------------
		//    Loop
		//--------------------------------------------------
		void Initialize() override;
		void Update() override;

		//--------------------------------------------------
		//    Data
		//--------------------------------------------------
		// CPU-side params; the engine never touches GPU shadow-map resources directly -
		// those live behind pompeii::Renderer::CreateLight/UpdateLight/DestroyLight.
		glm::vec3 dirPos{};
		glm::vec3 color{};
		float luxLumen{};
		pompeii::LightType type{};

		pompeii::LightHandle lightHandle{};
	};
}

#endif // GENERAL_LIGHT_H
