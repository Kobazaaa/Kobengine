// -- Standard Library --
#include <thread>

// -- Kobengine Includes --
// -- App --
#include "Application.h"
#include "LayerStack.h"

// -- Systems --
#include "RenderSystem.h"
#include "LightingSystem.h"

// -- Helper --
#include "AssetManager.h"
#include "InputManager.h"
#include "Timer.h"
#include "SceneManager.h"
#include "ServiceLocator.h"

// -- Components --
#include "Camera.h"
#include "LightComponent.h"
#include "MeshFilter.h"
#include "MeshRenderer.h"

// -- Platform --
#include "InputHandlerGLFW.h"

//--------------------------------------------------
//    Constructor & Destructor
//--------------------------------------------------
kobengine::Application::Application(const pompeii::WindowSettings& windowSettings)
{
	// -- Create --
	m_pWindow = std::make_unique<WindowGLFW>(windowSettings);
	m_pLayerStack = std::make_unique<LayerStack>();

	// -- Create Renderer --
	m_pRenderLayer = dynamic_cast<RenderLayer*>(m_pLayerStack->PushLayer(std::make_unique<RenderLayer>(m_pWindow.get())));

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
	InputManager::SetInputHandler(std::make_unique<InputHandlerGLFW>(static_cast<WindowGLFW*>(m_pWindow.get())));

	auto& scene = ServiceLocator::Get<SceneManager>().CreateScene("DefaultScene");
	ServiceLocator::Get<SceneManager>().SetActiveScene(scene);

	// cam
	auto& camera = scene.AddEmpty("Camera");
	auto cameraComp = camera.AddComponent<Camera>(CameraSettings{ .fov = 45.f, .aspectRatio = m_pWindow->GetAspectRatio(), .nearPlane = 0.001f, .farPlane = 1000.f }, true);

	// model
	auto& model = scene.AddEmpty("Model");
	auto filter = model.AddComponent<MeshFilter>();
	pompeii::Mesh* pMesh = ServiceLocator::Get<AssetManager>().LoadMesh("models/Sponza.gltf");
	filter->pMesh = pMesh;
	model.AddComponent<MeshRenderer>(*filter);

	InputManager::RegisterCommand(KeyCode::LSHIFT, TriggerState::Press, [cameraComp]	{ cameraComp->Speed *= 4.f; });
	InputManager::RegisterCommand(KeyCode::LSHIFT, TriggerState::Release, [cameraComp]	{ cameraComp->Speed *= .25f; });

	InputManager::RegisterCommand(KeyCode::W, TriggerState::Hold, [&, cameraComp] { camera.transform->Translate(Timer::GetDeltaSeconds() * cameraComp->Speed * camera.transform->GetForward()); });
	InputManager::RegisterCommand(KeyCode::A, TriggerState::Hold, [&, cameraComp] { camera.transform->Translate(-Timer::GetDeltaSeconds() * cameraComp->Speed * camera.transform->GetRight()); });
	InputManager::RegisterCommand(KeyCode::S, TriggerState::Hold, [&, cameraComp] { camera.transform->Translate(-Timer::GetDeltaSeconds() * cameraComp->Speed * camera.transform->GetForward()); });
	InputManager::RegisterCommand(KeyCode::D, TriggerState::Hold, [&, cameraComp] { camera.transform->Translate(Timer::GetDeltaSeconds() * cameraComp->Speed * camera.transform->GetRight()); });
	InputManager::RegisterCommand(KeyCode::Q, TriggerState::Hold, [&, cameraComp] { camera.transform->Translate(Timer::GetDeltaSeconds() * cameraComp->Speed * glm::vec3(0, -1, 0)); });
	InputManager::RegisterCommand(KeyCode::E, TriggerState::Hold, [&, cameraComp] { camera.transform->Translate(Timer::GetDeltaSeconds() * cameraComp->Speed * glm::vec3(0, 1, 0)); });

	InputManager::RegisterCommand(MouseButton::Left, TriggerState::Hold, [&, cameraComp]
	{
		glm::vec3 euler = camera.transform->GetEulerAngles();
		float pitch = euler.x + InputManager::GetMouseDelta().y * cameraComp->Sensitivity;
		float yaw = euler.y + InputManager::GetMouseDelta().x * cameraComp->Sensitivity;
		pitch = std::clamp(pitch, -89.f, 89.f);
		float roll = euler.z;
		camera.transform->SetEulerAngles({ pitch, yaw, roll });
	});

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
	Timer::Update();

	m_pWindow->PollEvents();
	InputManager::ProcessInput();

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
	m_pRenderLayer->GetRenderer()->GetContext().device.WaitIdle();
	ServiceLocator::Deregister<SceneManager>();
	ServiceLocator::Get<AssetManager>().UnloadAll();
	ServiceLocator::Deregister<AssetManager>();
	ServiceLocator::Deregister<LightingSystem>();
	ServiceLocator::Deregister<RenderSystem>();

	m_pLayerStack->DetachAllLayers();
}
