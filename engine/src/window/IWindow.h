#ifndef IWINDOW_H
#define IWINDOW_H

// -- Standard Library --
#include <string>

// -- Math Includes --
#include "glm/vec2.hpp"

namespace kobengine
{
	//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//? ~~	  Settings	
	//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct WindowSettings
	{
		std::string title = "Default Window";
		int width = 600;
		int height = 800;
	};

	//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//? ~~	  Window Interface	
	//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	class IWindow
	{
	public:
		//--------------------------------------------------
		//    Constructor & Destructor
		//--------------------------------------------------
		virtual ~IWindow() = default;

		//--------------------------------------------------
		//    Lifecycle
		//--------------------------------------------------
		virtual void PollEvents()											= 0;
		virtual bool ShouldClose() const									= 0;
		virtual void Close()												= 0;

		//--------------------------------------------------
		//    Properties
		//--------------------------------------------------
		virtual void SetTitle(const std::string& title)						= 0;
		virtual float GetAspectRatio()							const		= 0;
		virtual glm::ivec2 GetFramebufferSize()					const		= 0;
		virtual bool IsFullScreen()								const		= 0;
		virtual void ToggleFullScreen()										= 0;

		virtual bool IsOutdated()								const		= 0;
		virtual void ResetOutdated()										= 0;

		//--------------------------------------------------
		//    Handle
		//--------------------------------------------------
		virtual void* GetNativeHandle()							const		= 0;
	};
}

#endif // IWINDOW_H