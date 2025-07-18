// STD
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <thread>

// WIN32
#if WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

// SDL
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

// Includes
#include "Kobengine.h"

#include "InputManager.h"
#include "LoggerSoundSystem.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Timer.h"
#include "ServiceLocator.h"
#include "SDLSoundSystem.h"
#include "DefaultCollisionSystem.h"

//--------------------------------------------------
//    Constructor & Destructor
//--------------------------------------------------
kob::Kobengine::Kobengine()
{
	PrintSDLVersion();

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_pWindow = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_pWindow == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	auto assetPath = FindAssetsFolder();

	// Initial Setup
	Renderer::GetInstance().Init(m_pWindow);
	ResourceManager::GetInstance().Init(assetPath);

	// Setup Service Locators
	ServiceLocator::RegisterCollisionService(std::make_unique<DefaultCollisionSystem>());
#if _DEBUG
	ServiceLocator::RegisterSoundService(std::make_unique<LoggerSoundSystem>(std::make_unique<SDLSoundSystem>()));
#else
	ServiceLocator::RegisterSoundService(std::make_unique<SDLSoundSystem>());
#endif

}
kob::Kobengine::~Kobengine()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_pWindow);
	m_pWindow = nullptr;
	SDL_Quit();
}


//--------------------------------------------------
//    Loop
//--------------------------------------------------
//thank you to Mat in the Programming4 Discord Server of DAE for this nice function to find the assets folder :)
std::filesystem::path kob::Kobengine::FindAssetsFolder()
{
	constexpr uint32_t MAX_TRAVERSAL{ 5 };
	std::filesystem::path current = std::filesystem::current_path();

	for (uint32_t level{}; level < MAX_TRAVERSAL; ++level)
	{
		std::filesystem::path target = current / "assets";
		if (std::filesystem::exists(target))
			return target;

		current = current.parent_path();
	}
	std::cerr << "Assets folder not found after " << MAX_TRAVERSAL << " traversals.\n";
	return {};
}
void kob::Kobengine::Run()
{
	SceneManager::GetInstance().Start();
	Timer::Start();

	while (!m_Quit)
		RunOneFrame();
}
void kob::Kobengine::RunOneFrame()
{
	Timer::Update();

	m_Quit = !InputManager::GetInstance().ProcessInput();

	while (Timer::DoFixedTimeStep())
	{
		SceneManager::GetInstance().FixedUpdate();
	}

	SceneManager::GetInstance().Update();
	ServiceLocator::GetCollisionService().EvaluateCollisions();
	SceneManager::GetInstance().LateUpdate();
	Renderer::GetInstance().Render();

	std::this_thread::sleep_for(Timer::SleepDurationNanoSeconds());
}

//--------------------------------------------------
//    Loop
//--------------------------------------------------
glm::ivec2 kob::Kobengine::GetWindowSize()						{ glm::ivec2 size; SDL_GetWindowSize(m_pWindow, &size.x, &size.y); return size; }
void kob::Kobengine::SetWindowSize(int width, int height)		{ SDL_SetWindowSize(m_pWindow, width, height); }
void kob::Kobengine::SetWindowTitle(const std::string& title)	{ SDL_SetWindowTitle(m_pWindow, title.c_str()); }


//--------------------------------------------------
//    SDL Version Logging
//--------------------------------------------------

// Why bother with this? Because sometimes students have a different SDL version installed on their pc.
// That is not a problem unless for some reason the dll's from this project are not copied next to the exe.
// These entries in the debug output help to identify that issue.
void kob::Kobengine::PrintSDLVersion()
{
	SDL_version version{};
	SDL_VERSION(&version);
	LogSDLVersion("We compiled against SDL version ", version);

	SDL_GetVersion(&version);
	LogSDLVersion("We linked against SDL version ", version);

	SDL_IMAGE_VERSION(&version);
	LogSDLVersion("We compiled against SDL_image version ", version);

	version = *IMG_Linked_Version();
	LogSDLVersion("We linked against SDL_image version ", version);

	SDL_TTF_VERSION(&version)
		LogSDLVersion("We compiled against SDL_ttf version ", version);

	version = *TTF_Linked_Version();
	LogSDLVersion("We linked against SDL_ttf version ", version);
}
void kob::Kobengine::LogSDLVersion(const std::string& message, const SDL_version& v)
{
#if WIN32
	std::stringstream ss;
	ss << message << static_cast<int>(v.major) << "." << static_cast<int>(v.minor) << "." << static_cast<int>(v.patch) << "\n";
	OutputDebugString(ss.str().c_str());
#else
	std::cout << message << static_cast<int>(v.major) << "." << static_cast<int>(v.minor) << "." << static_cast<int>(v.patch) << "\n";
#endif
}
