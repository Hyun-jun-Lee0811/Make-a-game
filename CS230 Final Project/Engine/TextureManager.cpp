/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: TextureManager.cpp
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022/4/29
-----------------------------------------------------------------*/
#include "TextureManager.h"
#include "Texture.h"
#include "Engine.h"

CS230::Texture* CS230::TextureManager::Load(const std::filesystem::path& filePath)
{
	if (pathToTexture.find(filePath) == pathToTexture.end())
	{
		pathToTexture[filePath] = new Texture(filePath);
	}
	return pathToTexture[filePath];
}

void CS230::TextureManager::Unload()
{
	Engine::GetLogger().LogEvent("Clear Texture");
	for (std::pair<std::filesystem::path, Texture*> T : pathToTexture)
	{
		delete T.second;
	}
	pathToTexture.clear();
}