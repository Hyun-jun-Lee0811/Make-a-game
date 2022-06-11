/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Assignment: CS230 Final Project
File Name: Background.h
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022/4/16 spring
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\Texture.h"
#include "../Engine/TextureManager.h"
#include "..\Engine\Component.h"

namespace CS230
{
	class Camera;
}

class Background : public CS230::Component
{
public:
	~Background();
	void Add(const std::filesystem::path& texturePath, int level);
	void Draw(const CS230::Camera& camera);
	math::ivec2 Size();

private:
	struct ParallaxInfo
	{
		CS230::Texture* texturePtr;
		int level;
	};
	std::vector<ParallaxInfo> backgrounds;
};