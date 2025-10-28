#ifndef WINDOW_H
#define WINDOW_H

// -- GLFW Includes --
#include <GLFW/glfw3.h>

// -- Kobengine Includes --
#include "IWindow.h"

// -- Class --
namespace kobengine
{
	//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//? ~~	  WindowGLFW	
	//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	class WindowGLFW final : public IWindow
	{
	public:
		//--------------------------------------------------
		//    Constructor & Destructor
		//--------------------------------------------------
		explicit WindowGLFW(const WindowSettings& windowSettings);
		~WindowGLFW() override;

		//--------------------------------------------------
		//    Lifecycle
		//--------------------------------------------------
		void PollEvents()										override;
		bool ShouldClose()								const	override;
		void Close()											override;

		//--------------------------------------------------
		//    Properties
		//--------------------------------------------------
		void SetTitle(const std::string& title)					override;
		float GetAspectRatio()							const	override;
		glm::ivec2 GetFramebufferSize()					const	override;
		bool IsFullScreen()								const	override;
		void ToggleFullScreen()									override;
		bool IsOutdated()								const	override;
		void ResetOutdated()									override;

		//--------------------------------------------------
		//    Handle
		//--------------------------------------------------
		void* GetNativeHandle()							const	override;

	private:
		// Callback for when the window gets resized
		static void FrameBufferResizeCallback(GLFWwindow* window, int width, int height);

		GLFWwindow* m_pWindow		{ nullptr };
		bool m_Fullscreen			{ false };
		bool m_IsOutdated			{ false };
		glm::ivec2 m_WindowedPos	{ };
		glm::ivec2 m_WindowedSize	{ };
	};
}
#endif // WINDOW_H
