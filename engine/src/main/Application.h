#ifndef KOBENGINE_APPLICATION_H
#define KOBENGINE_APPLICATION_H

// -- Kobengine Includes --
#include "IWindow.h"

namespace kobengine
{
	class Application
	{
	public:
		//--------------------------------------------------
		//    Constructor & Destructor
		//--------------------------------------------------
		explicit Application(const WindowSettings& windowSettings);
		virtual ~Application() = default;

		//--------------------------------------------------
		//    Loop
		//--------------------------------------------------
		void Run();
		void RunOneFrame();

	protected:
		virtual void Shutdown();

		std::unique_ptr<IWindow> m_pWindow;
		//std::shared_ptr<pompeii::Renderer> m_pRenderer;
	};

	Application* CreateApplication();
}

#endif // KOBENGINE_APPLICATION_H