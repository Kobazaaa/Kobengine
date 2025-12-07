#ifndef CAMERA_COMPONENT_H
#define CAMERA_COMPONENT_H

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

		float Speed			{ 1.f };
		float Sensitivity	{ 0.1f };
		bool UseAutoExposure{ true };
		pompeii::ManualExposureSettings ManualExposureSettings{ };
		pompeii::AutoExposureSettings AutoExposureSettings{ };

		// -- Matrices --
		glm::mat4 GetViewMatrix() const;
		glm::mat4 GetProjectionMatrix();

	private:
		glm::mat4 m_ProjectionMatrix { };

		// -- Settings --
		CameraSettings m_Settings { };

		// -- Dirty Flags
		bool m_SettingsDirty { true };
	};
}

#endif // CAMERA_COMPONENT_H