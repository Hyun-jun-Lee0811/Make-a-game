/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Assignment: CS230 Final Project
File Name: Mode2.cpp
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022/4/16 spring
-----------------------------------------------------------------*/
#include "Mode3.h"
#include "../Engine/Engine.h"
#include "Screens.h"
#include "Fonts.h"
#include "../Engine/ShowCollision.h"
#include "GameParticles.h"
#include "Timer.h"
#include "Score.h"
#include "Gravity.h"
#include "Exit.h"
#include "Bird.h"
#include "LightningCloud.h"
#include "Win.h"

#include <doodle/doodle.hpp>

Mode3::Mode3() : mainmenu(CS230::InputKey::Keyboard::Escape), Reload(CS230::InputKey::Keyboard::R),
back(nullptr), gameObjectManager(nullptr), playerPtr(nullptr), lives(5) {}

void Mode3::Load()
{
	CS230::Camera2* cameraPtr = new CS230::Camera2({ { 0.15 * Engine::GetWindow().GetSize().x, 0 }, {0.35 * Engine::GetWindow().GetSize().x, 0 } });
	AddGSComponent(cameraPtr);
	AddGSComponent(new Background());
	back = GetGSComponent<Background>();
	back->Add("Assets/Mode3_background.png", 1);

	cameraPtr->SetExtent({ { 0,0 }, { back->Size() - Engine::GetWindow().GetSize() } });
	playerPtr = new Player({ 200 , Mode3::cloud_floor });
	gameObjectManager = new CS230::GameObjectManager;
	AddGSComponent(gameObjectManager);
	gameObjectManager->Add(playerPtr);

	gameObjectManager->Add(new Cloud({ 200, 250 }, 2));//1
	gameObjectManager->Add(new Cloud({ 360, 270 }, 3));//2
	gameObjectManager->Add(new Cloud({ 86, 270 }, 3));//3
	gameObjectManager->Add(new LightningCloud({ 680, 440 }));//4
	gameObjectManager->Add(new Cloud({ 880, 680 }, 1));//5
	gameObjectManager->Add(new Bird({ 240, 780 }, { 200, 520 }, playerPtr));//6
	gameObjectManager->Add(new Cloud({ 180, 700 }, 1));//7
	gameObjectManager->Add(new LightningCloud({ 50, 880 }));//8
	gameObjectManager->Add(new Cloud({ 306, 1100 }, 3));//9
	gameObjectManager->Add(new Cloud({ -70, 1050 }, 2));//10
	gameObjectManager->Add(new Cloud({ 506, 1200 }, 3));//11
	gameObjectManager->Add(new Cloud({ 706, 1300 }, 3));//12
	gameObjectManager->Add(new Cloud({ 906, 1400 }, 3));//13
	gameObjectManager->Add(new Cloud({ 1106, 1580 }, 1));//14
	gameObjectManager->Add(new LightningCloud({ 1300, 1680 }));//15
	gameObjectManager->Add(new LightningCloud({ 900, 1880 }));//16
	gameObjectManager->Add(new Cloud({ 580, 2000 }, 2));//17
	gameObjectManager->Add(new Cloud({ 80, 2200 }, 1));//18
	gameObjectManager->Add(new Bird({ 60, 2300 }, { 60, 200 }, playerPtr));//19
	gameObjectManager->Add(new LightningCloud({ 600, 2400 }));//20
	gameObjectManager->Add(new Cloud({ 1100, 2650 }, 1));//21
	gameObjectManager->Add(new LightningCloud({ 1300, 2750 }));//22
	gameObjectManager->Add(new Cloud({ 900, 2900 }, 2));//23
	gameObjectManager->Add(new Cloud({ 400, 3000 }, 1));//24
	gameObjectManager->Add(new Cloud({ 0, 3200 }, 1));//25
	gameObjectManager->Add(new Cloud({ 400, 3400 }, 1));//26
	gameObjectManager->Add(new Cloud({ 800, 3400 }, 1));//27
	gameObjectManager->Add(new Cloud({ 1340, 3500 }, 3));//28
	gameObjectManager->Add(new Cloud({ 1000, 3650 }, 2));//29
	gameObjectManager->Add(new LightningCloud({ 680, 3800 }));//30
	gameObjectManager->Add(new LightningCloud({ 340, 3970 }));//31
	gameObjectManager->Add(new Cloud({ 40, 4100 }, 3));//32
	gameObjectManager->Add(new LightningCloud({ -130, 4370 }));//31
	gameObjectManager->Add(new Cloud({ 270, 4550 }, 2));//32
	gameObjectManager->Add(new Cloud({ 600, 4650 }, 3));//33
	gameObjectManager->Add(new Cloud({ 900, 4800 }, 3));//34
	gameObjectManager->Add(new LightningCloud({ 1200, 5050 }));//35
	gameObjectManager->Add(new LightningCloud({ 1400, 5250 }));//35
	gameObjectManager->Add(new Cloud({ 760, 5360 }, 1));//27
	gameObjectManager->Add(new Cloud({ 200, 5160 }, 1));//29

	gameObjectManager->Add(new Bird({ 100, 1780 }, { 200, 1200 }, playerPtr));//6
	gameObjectManager->Add(new Bird({ 100, 2780 }, { 200, 1200 }, playerPtr));//6
	gameObjectManager->Add(new Bird({ 100, 3780 }, { 200, 1200 }, playerPtr));//6
	gameObjectManager->Add(new Bird({ 100, 4780 }, { 200, 1200 }, playerPtr));//6
	gameObjectManager->Add(new Exit({ {300, static_cast<int>(Mode3::cloud_floor) + 4800}, {500, 500} }));
	//gameObjectManager->Add(new EnemyShip(playerPtr));

	GameOverTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font2)).DrawTextToTexture("Game Over", 0xFFFFFFFF, true);
	MainMenuTextue = Engine::GetSpriteFont(static_cast<int>(Fonts::Font2)).DrawTextToTexture("Press Escape to MainMenu", 0xFFFFFFFF, true);

	std::string livesString = "Lives: " + std::to_string(lives);
	livesTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture(livesString, 0xFFFFFFFF, true);

	AddGSComponent(new Score(0, Fonts::Font1));
	AddGSComponent(new Timer(120));
	AddGSComponent(new Gravity(1875));
	AddGSComponent(new CrushEmitter());
#ifdef _DEBUG
	AddGSComponent(new ShowCollision(CS230::InputKey::Keyboard::Tilde));
#endif
}

void Mode3::Update(double dt)
{
	GetGSComponent<CS230::Camera2>()->Update(playerPtr->GetPosition());
#ifdef _DEBUG
	if (mainmenu.IsKeyReleased() == true && playerPtr->IsDead() == false)
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
	}
	GetGSComponent<ShowCollision>()->Update(dt);
#else
	if (Reload.IsKeyReleased() == true && playerPtr->IsDead() == false)
	{
		Engine::GetGameStateManager().ReloadState();
	}
#endif
	if (Reload.IsKeyReleased() == true && playerPtr->IsDead() == false)
	{
		Engine::GetGameStateManager().ReloadState();
	}

	gameObjectManager->Update(dt);
	if (lives > 0)
	{
		if (playerPtr->IsDead() == false)
		{
			GetGSComponent<Timer>()->Update(dt);
			GetGSComponent<Score>()->Update(dt);
		}
	}

	if (GetGSComponent<Timer>()->hasEnded())
	{
		lives -= 1;
		if (lives <= 0)
		{
			lives = 5;
			Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
		}
		else
		{
			Engine::GetGameStateManager().ReloadState();
		}
	}

	if (playerPtr->IsDead() == true)
	{
		lives -= 1;
		if (lives > 0)
		{
			Engine::GetGameStateManager().ReloadState();
		}
		else if (mainmenu.IsKeyReleased() == true && lives <= 0)
		{
			lives = 5;
			Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
		}
	}
}

void Mode3::Unload()
{
	ClearGSComponent();
	playerPtr = nullptr;
}

void Mode3::Draw()
{
	Engine::GetWindow().Clear(0x000000FF);
	CS230::Camera2* cameraPtr = GetGSComponent<CS230::Camera2>();
	GetGSComponent<Background>()->Draw2(*cameraPtr);
	math::TransformMatrix cameraMatrix = cameraPtr->GetMatrix();
	gameObjectManager->DrawAll(cameraMatrix);
	math::ivec2 winSize = Engine::GetWindow().GetSize();
	if (lives > 0)
	{
		if (playerPtr->IsDead() == false)
		{
			GetGSComponent<Score>()->Draw(math::ivec2{ 10, winSize.y - 90 });
			livesTexture.Draw(math::TranslateMatrix(math::ivec2{ winSize.x * 2 / 5, winSize.y - livesTexture.GetSize().y - 5 }));
			GetGSComponent<Timer>()->Draw(math::ivec2{ winSize.x * 3 / 4, winSize.y - 90 });
		}
	}

	if (lives <= 0)
	{
		if (playerPtr->IsDead() == true)
		{
			MainMenuTextue.Draw(math::TranslateMatrix{ math::ivec2
				{Engine::GetWindow().GetSize().x / 2 - MainMenuTextue.GetSize().x / 2,winSize.y / 2 - GameOverTexture.GetSize().y } });
			GameOverTexture.Draw(math::TranslateMatrix{ math::ivec2
				{Engine::GetWindow().GetSize().x / 2 - GameOverTexture.GetSize().x / 2,winSize.y / 2 } });
		}
	}
}