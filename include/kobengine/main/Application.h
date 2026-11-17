#ifndef KOBENGINE_APPLICATION_H
#define KOBENGINE_APPLICATION_H

// -- Standard Library --
#include <memory>

// -- Pompeii Includes --
#include "IWindow.h"

// -- Kobengine Includes --
#include "LayerStack.h"
#include "Renderer.h"
#include "RenderLayer.h"

namespace kobengine
{
	//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//? ~~	  Application	
	//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	class Application
	{
	public:
		//--------------------------------------------------
		//    Constructor & Destructor
		//--------------------------------------------------
		explicit Application(const pompeii::WindowSettings& windowSettings);
		virtual ~Application() = default;

		//--------------------------------------------------
		//    Loop
		//--------------------------------------------------
		void Run();
		void RunOneFrame();

	protected:
		virtual void Shutdown();

		std::unique_ptr<pompeii::IWindow> m_pWindow;
		std::unique_ptr<LayerStack> m_pLayerStack;
		RenderLayer* m_pRenderLayer;
	};

	Application* CreateApplication();
}

#endif // KOBENGINE_APPLICATION_H