// -- Standard Library --
#include <thread>

// -- Kobengine Includes --
#include "Application.h"
#include "Timer.h"
#include "ServiceLocator.h"
#include "WindowGLFW.h"

//--------------------------------------------------
//    Constructor & Destructor
//--------------------------------------------------
kobengine::Application::Application(const WindowSettings& windowSettings)
{
	// -- Create Window --
	m_pWindow = std::make_unique<WindowGLFW>(windowSettings);

	// -- Register Services --
	//m_pRenderer = std::make_shared<pompeii::Renderer>(m_pWindow);
	//ServiceLocator::Register(std::make_unique<SceneManager>());
	//ServiceLocator::Register(std::make_unique<RenderSystem>());
	//ServiceLocator::Register(std::make_unique<LightingSystem>());

	//ServiceLocator::Get<LightingSystem>().SetRenderer(m_pRenderer);
	//ServiceLocator::Get<RenderSystem>().SetRenderer(m_pRenderer);
	//m_pRenderer->InsertUI([]
	//	{
	//		ServiceLocator::Get<Editor>().Draw();
	//	});

}


//--------------------------------------------------
//    Loop
//--------------------------------------------------
void kobengine::Application::Run()
{
	//ServiceLocator::Get<SceneManager>().Start();
	Timer::Start();

	while (!m_pWindow->ShouldClose())
		RunOneFrame();
}
void kobengine::Application::RunOneFrame()
{
	Timer::Update();

	//auto& sceneManager = ServiceLocator::Get<SceneManager>();
	//sceneManager.Update();
	//m_pRendererm_pRenderer->Render();

	std::this_thread::sleep_for(Timer::SleepDurationNanoSeconds());
}

void kobengine::Application::Shutdown()
{
}
