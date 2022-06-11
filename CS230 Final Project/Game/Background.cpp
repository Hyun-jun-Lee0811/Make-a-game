/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Background.cpp
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022/4/16 spring
-----------------------------------------------------------------*/
#include "Background.h"
#include "../Engine/Camera.h"
#include "../Engine/Engine.h"


void Background::Add(const std::filesystem::path& texturePath, int level)
{
	backgrounds.push_back(ParallaxInfo{ Engine::GetTextureManager().Load(texturePath), level });
}

void Background::Draw(const CS230::Camera& camera)
{
	for (int i = 0; i < backgrounds.size(); i++)
	{
		backgrounds[i].texturePtr->Draw(math::TranslateMatrix(-camera.GetPosition() / backgrounds[i].level));
	}
}

Background::~Background()
{
	backgrounds.clear();
}

math::ivec2 Background::Size()
{
	for (ParallaxInfo& levels : backgrounds)
	{
		if (levels.level == 1)
		{
			return levels.texturePtr->GetSize();
		}
	}
	return { 0,0 };
}