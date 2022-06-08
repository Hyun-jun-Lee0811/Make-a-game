/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: TextureManager.h
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022/4/29
-----------------------------------------------------------------*/
#pragma once
#include <filesystem>
#include <map>

namespace CS230
{
	class Texture;

	class TextureManager
	{
	public:
		Texture* Load(const std::filesystem::path& filePath);
		void Unload();

	private:
		std::map<std::filesystem::path, Texture*> pathToTexture;
	};
}