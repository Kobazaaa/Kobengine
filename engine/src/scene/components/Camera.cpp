// -- Standard Library --
#include <algorithm>
#include <iostream>

// -- Keyboard --
#include "GLFW/glfw3.h"

// -- Kobengine Includes --
#include "Camera.h"
#include "ServiceLocator.h"
#include "SceneObject.h"
#include "IWindow.h"
#include "Timer.h"
#include "RenderSystem.h"


//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//? ~~	  CLASS HERE	
//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//--------------------------------------------------
//    Constructor & Destructor
//--------------------------------------------------
kobengine::Camera::Camera(SceneObject& parent, const CameraSettings& settings, const IWindow* pWindow, bool mainCam)
	: Component(parent, "Camera")
	, m_Settings(settings)
	, m_ManualExposureSettings{ .aperture = 16.f, .shutterSpeed = 1.f / 100.f, .iso = 100.f}
	, m_AutoExposureSettings{ .minLogLum = -8.f, .logLumRange = 12.f }
	, m_pWindow(pWindow->GetNativeHandle())
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
{
	if (!m_pWindow)
		std::cerr << "Window not valid for Camera!\n";
	HandleAim();
	HandleMovement();

	//const auto& io = ImGui::GetIO();
	//if (!io.WantCaptureMouse)
	//if (!io.WantCaptureKeyboard)
}


//--------------------------------------------------
//    Accessors & Mutators
//--------------------------------------------------
// -- Settings --
void kobengine::Camera::ChangeSettings(const CameraSettings& settings) { m_Settings = settings; m_SettingsDirty = true; }
const kobengine::CameraSettings& kobengine::Camera::GetSettings() const	{ return m_Settings; }

const pompeii::ManualExposureSettings& kobengine::Camera::GetManualExposureSettings() const { return m_ManualExposureSettings; }
const pompeii::AutoExposureSettings& kobengine::Camera::GetAutoExposureSettings() const { return m_AutoExposureSettings; }
bool kobengine::Camera::IsAutoExposureEnabled() const { return m_AutoExposure; }

void kobengine::Camera::SetSpeed(float speed) { m_Speed = speed; }
void kobengine::Camera::SetSensitivity(float sensitivity) { m_Sensitivity = sensitivity; }

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


//--------------------------------------------------
//    Helpers
//--------------------------------------------------
void kobengine::Camera::HandleMovement() const
{
	float speed = m_Speed * Timer::GetDeltaSeconds();
	auto window = static_cast<GLFWwindow*>(m_pWindow);
	speed *= glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? 4.f : 1.f;


	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		GetTransform().Translate(GetTransform().GetForward() * speed);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		GetTransform().Translate(-GetTransform().GetForward() * speed);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		GetTransform().Translate(-GetTransform().GetRight() * speed);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		GetTransform().Translate(GetTransform().GetRight() * speed);
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		GetTransform().Translate(glm::vec3(0, 1, 0) * speed);
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		GetTransform().Translate(glm::vec3(0, -1, 0) * speed);
	}
}
void kobengine::Camera::HandleAim()
{
	auto window = static_cast<GLFWwindow*>(m_pWindow);
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		double x, y;
		glfwGetCursorPos(window, &x, &y);

		if (!m_IsDragging)
		{
			m_IsDragging = true;
			m_LastX = static_cast<float>(x);
			m_LastY = static_cast<float>(y);
		}
		else
		{
			const float deltaX = static_cast<float>(x) - m_LastX;
			const float deltaY = static_cast<float>(y) - m_LastY;

			glm::vec3 euler = GetTransform().GetEulerAngles();
			float pitch = euler.x + deltaY * m_Sensitivity;
			float yaw = euler.y + deltaX * m_Sensitivity;
			pitch = std::clamp(pitch, -89.f, 89.f);
			float roll = euler.z;
			GetTransform().SetEulerAngles({ pitch, yaw, roll });

			m_LastX = static_cast<float>(x);
			m_LastY = static_cast<float>(y);
		}
	}
	else
		m_IsDragging = false;
}
