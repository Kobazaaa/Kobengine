// -- Kobengine Includes --
#include "WindowGLFW.h"


//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//? ~~	  Window	
//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//--------------------------------------------------
//    Constructor & Destructor
//--------------------------------------------------
kobengine::WindowGLFW::WindowGLFW(const WindowSettings& windowSettings)
{
	// -- Init --
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	m_Fullscreen = false;
	glfwGetWindowSize(m_pWindow, &m_WindowedSize.x, &m_WindowedSize.y);
	glfwGetWindowPos(m_pWindow, &m_WindowedPos.x, &m_WindowedPos.y);

	// -- Create Window --
	m_pWindow = glfwCreateWindow(windowSettings.width, windowSettings.height, windowSettings.title.c_str(), nullptr, nullptr);

	// -- Callbacks --
	glfwSetWindowUserPointer(m_pWindow, this);
	glfwSetFramebufferSizeCallback(m_pWindow, FrameBufferResizeCallback);
}

kobengine::WindowGLFW::~WindowGLFW()
{
	glfwDestroyWindow(m_pWindow);
	glfwTerminate();
}


//--------------------------------------------------
//    Lifecycle
//--------------------------------------------------
void kobengine::WindowGLFW::PollEvents()
{
	glfwPollEvents();
}
bool kobengine::WindowGLFW::ShouldClose() const
{
	return glfwWindowShouldClose(m_pWindow);
}
void kobengine::WindowGLFW::Close()
{
	glfwSetWindowShouldClose(m_pWindow, GLFW_TRUE);
}


//--------------------------------------------------
//    Properties
//--------------------------------------------------
void kobengine::WindowGLFW::SetTitle(const std::string& title)
{
	glfwSetWindowTitle(m_pWindow, title.c_str());
}
float kobengine::WindowGLFW::GetAspectRatio() const
{
	const auto fbSize = GetFramebufferSize();
	const float aspect = static_cast<float>(fbSize.x) / static_cast<float>(fbSize.y);
	return aspect;
}
glm::ivec2 kobengine::WindowGLFW::GetFramebufferSize() const
{
	int width;
	int height;
	glfwGetFramebufferSize(m_pWindow, &width, &height);
	return glm::ivec2(width, height);
}
bool kobengine::WindowGLFW::IsFullScreen() const
{
	return m_Fullscreen;
}
void kobengine::WindowGLFW::ToggleFullScreen()
{
	m_Fullscreen = !m_Fullscreen;
	if (!m_Fullscreen)
	{
		glfwSetWindowMonitor(
			m_pWindow, nullptr,
			m_WindowedPos.x, m_WindowedPos.y,
			m_WindowedSize.x, m_WindowedSize.y,
			GLFW_DONT_CARE);
	}
	else
	{
		glfwGetWindowPos(m_pWindow, &m_WindowedPos.x, &m_WindowedPos.y);
		glfwGetWindowSize(m_pWindow, &m_WindowedSize.x, &m_WindowedSize.y);

		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		glfwSetWindowMonitor(
			m_pWindow, glfwGetPrimaryMonitor(),
			0, 0,
			mode->width, mode->height,
			mode->refreshRate);
	}
}

bool kobengine::WindowGLFW::IsOutdated() const
{
	return m_IsOutdated;
}
void kobengine::WindowGLFW::ResetOutdated()
{
	m_IsOutdated = false;
}

//--------------------------------------------------
//    Handle
//--------------------------------------------------
void* kobengine::WindowGLFW::GetNativeHandle() const
{
	return m_pWindow;
}


//--------------------------------------------------
//    Callbacks
//--------------------------------------------------
void kobengine::WindowGLFW::FrameBufferResizeCallback(GLFWwindow* window, int, int)
{
	WindowGLFW* pWindow = static_cast<WindowGLFW*>(glfwGetWindowUserPointer(window));
	pWindow->m_IsOutdated = true;

	if (!pWindow->IsFullScreen())
	{
		glfwGetWindowPos(pWindow->m_pWindow, &pWindow->m_WindowedPos.x, &pWindow->m_WindowedPos.y);
		glfwGetWindowSize(pWindow->m_pWindow, &pWindow->m_WindowedSize.x, &pWindow->m_WindowedSize.y);
	}
}
