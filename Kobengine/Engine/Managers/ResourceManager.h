﻿#pragma once
#include <filesystem>
#include <string>
#include <memory>
#include <map>

#include "Singleton.h"

namespace kob
{
	class Texture2D;
	class Font;

	class ResourceManager final : public Singleton<ResourceManager>
	{
		//--------------------------------------------------
		//    Constructor & Destructor
		//--------------------------------------------------
	private:
		ResourceManager() = default;
	public:
		void Init(const std::filesystem::path& data);

		//--------------------------------------------------
		//    Accessors & Mutators
		//--------------------------------------------------
		std::shared_ptr<Texture2D> LoadTexture(const std::string& file);
		std::shared_ptr<Font> LoadFont(const std::string& file, uint8_t size);
	private:
		friend class Singleton<ResourceManager>;

		std::filesystem::path m_DataPath;
		void UnloadUnusedResources();

		std::map<std::string, std::shared_ptr<Texture2D>> m_mLoadedTextures;
		std::map<std::pair<std::string, uint8_t>, std::shared_ptr<Font>> m_mLoadedFonts;

	};
}
