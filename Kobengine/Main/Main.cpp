#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Kobengine.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"

#include <filesystem>
namespace fs = std::filesystem;

#include "FPSComponent.h"
#include "ImageRendererComponent.h"
#include "TextRendererComponent.h"
#include "RotateComponent.h"
#include "ThrashTheCacheComponent.h"

void load()
{
	auto& scene = kob::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<kob::GameObject>();
	go->AddComponent<kob::ImageRendererComponent>("background.tga");
	scene.Add(go);
	
	go = std::make_shared<kob::GameObject>();
	go->AddComponent<kob::ImageRendererComponent>("logo.tga");
	go->SetLocalPosition(glm::vec3(216, 180, 0));
	scene.Add(go);

	auto font = kob::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_shared<kob::GameObject>();
	go->AddComponent<kob::TextRendererComponent>("Programming 4 Assignment", font);
	go->SetLocalPosition(glm::vec3(80, 20, 0));
	scene.Add(go);

	go = std::make_shared<kob::GameObject>();
	go->AddComponent<kob::TextRendererComponent>("FPS", font);
	go->SetLocalPosition(glm::vec3(0, 450, 0));
	go->AddComponent<kob::FPSComponent>();
	scene.Add(go);


	auto emptyGo = std::make_shared<kob::GameObject>();
	emptyGo->SetLocalPosition(glm::vec3(300, 250, 0));
	scene.Add(emptyGo);

	auto chefGo = std::make_shared<kob::GameObject>();
	chefGo->AddComponent<kob::ImageRendererComponent>("Chef.png");
	chefGo->SetLocalPosition(glm::vec3(0, 0, 0));
	chefGo->SetParent(emptyGo.get(), false);
	chefGo->AddComponent<kob::RotateComponent>(0.5f, 150.f);
	scene.Add(chefGo);

	go = std::make_shared<kob::GameObject>();
	go->AddComponent<kob::ImageRendererComponent>("Bean.png");
	go->SetLocalPosition(glm::vec3(0, 0, 0));
	go->SetParent(chefGo.get(), false);
	go->AddComponent<kob::RotateComponent>(20.f, 50.f);
	scene.Add(go);

	go = std::make_shared<kob::GameObject>();
	go->AddComponent<kob::ThrashTheCacheComponent>();
	scene.Add(go);
}

int main(int, char*[]) {
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Resources/";
	if(!fs::exists(data_location))
		data_location = "../Resources/";
#endif
	kob::Kobengine engine(data_location);
	engine.Run(load);
    return 0;
}
