/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Splash.cpp
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022/4/16 Spring
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"
#include "Screens.h"
#include "Splash.h"

Splash::Splash() : texturePtr(nullptr) {}

void Splash::Load()
{
	texturePtr = Engine::GetTextureManager().Load("Assets/DigiPen_BLACK_1024px.png");
}

void Splash::Update(double dt)
{
	std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
	time += dt;
	if (time > 3.0)
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
	}
}

void Splash::Unload() {}

void Splash::Draw()
{
	Engine::GetWindow().Clear(0xFFFFFFFF);
	texturePtr->Draw(math::TranslateMatrix{ Engine::GetWindow().GetSize() / 2.0 - texturePtr->GetSize() / 2.0 });
}