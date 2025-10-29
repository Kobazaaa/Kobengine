#ifndef GENERAL_LIGHT_H
#define GENERAL_LIGHT_H

// -- Math Includes --
#include "glm/glm.hpp"

// -- Kobengine Includes --
#include "Component.h"
#include "Light.h"

// -- Forward Declarations --
namespace pompeii
{
	struct AABB;
}

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
		void Start() override;
		void Update() override;

		//--------------------------------------------------
		//    Accessors & Mutators
		//--------------------------------------------------
		pompeii::Light lightData{};
	};
}

#endif // GENERAL_LIGHT_H