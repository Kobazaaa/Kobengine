// -- Standard Library --
#include <algorithm>
#include <iostream>

// -- Kobengine Includes --
#include "Camera.h"
#include "ServiceLocator.h"
#include "SceneObject.h"
#include "Timer.h"
#include "RenderSystem.h"

//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//? ~~	  CLASS HERE	
//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//--------------------------------------------------
//    Constructor & Destructor
//--------------------------------------------------
kobengine::Camera::Camera(SceneObject& parent, const CameraSettings& settings, bool mainCam)
	: Component(parent, "Camera")
	, m_Settings(settings)
	, m_ManualExposureSettings{ .aperture = 16.f, .shutterSpeed = 1.f / 100.f, .iso = 100.f}
	, m_AutoExposureSettings{ .minLogLum = -8.f, .logLumRange = 12.f }
{
	if (mainCam)
		ServiceLocator::Get<RenderSystem>().SetMainCamera(*this);
}



//--------------------------------------------------
//    Loop
//--------------------------------------------------
void kobengine::Camera::Start()
{}
void kobengine::Camera::Update()
{}


//--------------------------------------------------
//    Accessors & Mutators
//--------------------------------------------------
// -- Settings --
void kobengine::Camera::ChangeSettings(const CameraSettings& settings) { m_Settings = settings; m_SettingsDirty = true; }
const kobengine::CameraSettings& kobengine::Camera::GetSettings() const	{ return m_Settings; }

const pompeii::ManualExposureSettings& kobengine::Camera::GetManualExposureSettings() const { return m_ManualExposureSettings; }
const pompeii::AutoExposureSettings& kobengine::Camera::GetAutoExposureSettings() const { return m_AutoExposureSettings; }
bool kobengine::Camera::IsAutoExposureEnabled() const { return m_AutoExposure; }

// -- Matrices --
glm::mat4 kobengine::Camera::GetViewMatrix() const
{
	return glm::inverse(GetTransform().GetMatrix());
}
glm::mat4 kobengine::Camera::GetProjectionMatrix()
{
	if (m_SettingsDirty)
	{
		m_SettingsDirty = false;
		m_ProjectionMatrix = glm::perspectiveLH(glm::radians(m_Settings.fov), m_Settings.aspectRatio,
															 m_Settings.nearPlane, m_Settings.farPlane);
		m_ProjectionMatrix[1][1] *= -1;
	}
	return m_ProjectionMatrix;
}
