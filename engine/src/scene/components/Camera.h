#ifndef CAMERA_COMPONENT_H
#define CAMERA_COMPONENT_H

// -- Defines --
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_FORCE_LEFT_HANDED
#define GLM_FORCE_RADIANS

// -- Math Includes --
#include <glm/glm.hpp>

// -- Kobengine Includes --
#include "Component.h"
#include "GPUCamera.h"

namespace kobengine
{
	//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//? ~~	  CameraSettings	
	//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct CameraSettings
	{
		float fov;
		float aspectRatio;
		float nearPlane;
		float farPlane;
	};

	//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//? ~~	  Camera	
	//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	class Camera final : public Component
	{
	public:
		//--------------------------------------------------
		//    Constructor & Destructor
		//--------------------------------------------------
		explicit Camera(SceneObject& parent, const CameraSettings& settings, bool mainCam = false);

		//--------------------------------------------------
		//    Loop
		//--------------------------------------------------
		void Start() override;
		void Update() override;

		//--------------------------------------------------
		//    Accessors & Mutators
		//--------------------------------------------------
		// -- Settings --
		void ChangeSettings(const CameraSettings& settings);
		const CameraSettings& GetSettings() const;
		const pompeii::ManualExposureSettings& GetManualExposureSettings() const;
		const pompeii::AutoExposureSettings& GetAutoExposureSettings() const;
		bool IsAutoExposureEnabled() const;

		void SetSpeed(float speed);
		void SetSensitivity(float sensitivity);

		// -- Matrices --
		glm::mat4 GetViewMatrix() const;
		glm::mat4 GetProjectionMatrix();

	private:
		// -- Helpers --
		void HandleMovement() const;
		void HandleAim();

		glm::mat4 m_ProjectionMatrix		{ };

		// -- Settings --
		CameraSettings	 m_Settings						{ };
		bool m_AutoExposure								{ true };
		pompeii::ManualExposureSettings m_ManualExposureSettings	{ };
		pompeii::AutoExposureSettings m_AutoExposureSettings		{ };

		float m_Speed						{ 1.f };
		float m_Sensitivity					{ 0.1f };

		bool m_IsDragging					{ false };
		float m_LastX						{ 0.f };
		float m_LastY						{ 0.f };

		// -- Dirty Flags
		bool m_SettingsDirty				{ true };
	};
}

#endif // CAMERA_COMPONENT_H