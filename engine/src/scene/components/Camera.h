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
		const pompeii::ManualExposureSettings& GetManualExposureSettings() const;
		const pompeii::AutoExposureSettings& GetAutoExposureSettings() const;
		bool IsAutoExposureEnabled() const;

		float Speed			{ 1.f };
		float Sensitivity	{ 0.1f };

		// -- Matrices --
		glm::mat4 GetViewMatrix() const;
		glm::mat4 GetProjectionMatrix();

	private:
		glm::mat4 m_ProjectionMatrix { };

		// -- Settings --
		CameraSettings	 m_Settings									{ };
		bool m_AutoExposure											{ true };
		pompeii::ManualExposureSettings m_ManualExposureSettings	{ };
		pompeii::AutoExposureSettings m_AutoExposureSettings		{ };

		// -- Dirty Flags
		bool m_SettingsDirty				{ true };
	};
}

#endif // CAMERA_COMPONENT_H