// -- Standard Library --
#include <thread>

// -- Kobengine Includes --
#include "Application.h"
#include "Timer.h"
#include "ServiceLocator.h"
#include "WindowGLFW.h"

#include "RenderSystem.h"
#include "LightingSystem.h"
#include "SceneManager.h"
#include "AssetManager.h"
#include "Camera.h"
#include "LayerStack.h"
#include "LightComponent.h"
#include "MeshFilter.h"
#include "MeshRenderer.h"

//--------------------------------------------------
//    Constructor & Destructor
//--------------------------------------------------
kobengine::Application::Application(const WindowSettings& windowSettings)
{
	// -- Create --
	m_pWindow = std::make_unique<WindowGLFW>(windowSettings);
	m_pLayerStack = std::make_unique<LayerStack>();

	// -- Create Renderer --
	m_pRenderLayer = dynamic_cast<RenderLayer*>(m_pLayerStack->PushLayer(std::make_unique<RenderLayer>()));

	// -- Register Services --
	ServiceLocator::Register(std::make_unique<SceneManager>());
	ServiceLocator::Register(std::make_unique<RenderSystem>());
	ServiceLocator::Register(std::make_unique<LightingSystem>());
	ServiceLocator::Register(std::make_unique<AssetManager>());

	auto renderer = m_pRenderLayer->GetRenderer();
	ServiceLocator::Get<LightingSystem>().SetRenderer(renderer);
	ServiceLocator::Get<RenderSystem>().SetRenderer(renderer);
	ServiceLocator::Get<AssetManager>().SetRenderer(renderer);
	//m_pRenderer->InsertUI([]
	//	{
	//		ServiceLocator::Get<Editor>().Draw();
	//	});


	auto& scene = ServiceLocator::Get<SceneManager>().CreateScene("DefaultScene");
	ServiceLocator::Get<SceneManager>().SetActiveScene(scene);

	// cam
	auto& camera = scene.AddEmpty("Camera");
	camera.AddComponent<Camera>(CameraSettings{ .fov = 45.f, .aspectRatio = m_pWindow->GetAspectRatio(), .nearPlane = 0.001f, .farPlane = 1000.f }, m_pWindow.get(), true);

	// model
	auto& model = scene.AddEmpty("Model");
	auto filter = model.AddComponent<MeshFilter>();
	pompeii::Mesh* pMesh = ServiceLocator::Get<AssetManager>().LoadMesh("models/FlightHelmet.gltf");
	filter->pMesh = pMesh;
	model.AddComponent<MeshRenderer>(*filter);

	// light
	auto& light1 = scene.AddEmpty("SunLight");
	light1.AddComponent<LightComponent>(
			/* direction */	glm::vec3{ 0.577f, -0.577f, 0.577f },
			/* color */		glm::vec3{ 1.f, 1.f, 1.f },
			/* lux */			20.f, pompeii::LightType::Directional
	);

	auto& light2 = scene.AddEmpty("GreenLight");
	light2.AddComponent<LightComponent>(
			/* position */		glm::vec3{ 3.f, 0.5f, 0.f },
			/* color */		glm::vec3{ 0.f, 1.f, 0.f },
			/* lumen */		1000.f, pompeii::LightType::Point
	);

	auto& light3 = scene.AddEmpty("YellowLight");
	light3.AddComponent<LightComponent>(
			/* position */		glm::vec3{ 7.f, 0.5f, 0.f },
			/* color */		glm::vec3{ 1.f, 1.f, 0.f},
			/* lumen */		1200.f, pompeii::LightType::Point
	);

}


//--------------------------------------------------
//    Loop
//--------------------------------------------------
void kobengine::Application::Run()
{
	ServiceLocator::Get<SceneManager>().Start();
	Timer::Start();

	while (!m_pWindow->ShouldClose())
		RunOneFrame();

	Shutdown();
}
void kobengine::Application::RunOneFrame()
{
	m_pWindow->PollEvents();
	Timer::Update();


	// --- Begin Frame Phase ---
	ServiceLocator::Get<LightingSystem>().BeginFrame();
	ServiceLocator::Get<RenderSystem>().BeginFrame();
	
	// -- Update Phase --
	ServiceLocator::Get<SceneManager>().Update();
	ServiceLocator::Get<LightingSystem>().Update();
	ServiceLocator::Get<RenderSystem>().Update();
	
	// -- Render Phase --
	m_pLayerStack->UpdateAllLayers();

	// -- End Frame Phase --
	ServiceLocator::Get<LightingSystem>().EndFrame();
	ServiceLocator::Get<RenderSystem>().EndFrame();


	std::this_thread::sleep_for(Timer::SleepDurationNanoSeconds());
}

void kobengine::Application::Shutdown()
{
	pRenderLayer->GetRenderer()->GetContext().device.WaitIdle();
	ServiceLocator::Deregister<SceneManager>();
	ServiceLocator::Get<AssetManager>().UnloadAll();
	ServiceLocator::Deregister<AssetManager>();
	ServiceLocator::Deregister<LightingSystem>();
	ServiceLocator::Deregister<RenderSystem>();

	m_pLayerStack->DetachAllLayers();
}
