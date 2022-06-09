/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
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

#include <doodle/doodle.hpp>

Mode3::Mode3() : mainmenu(CS230::InputKey::Keyboard::Escape), Reload(CS230::InputKey::Keyboard::R),
back(nullptr), gameObjectManager(nullptr), playerPtr(nullptr), lives(5) {}

void Mode3::Load()
{
	CS230::Camera* cameraPtr = new CS230::Camera({ { 0.15 * Engine::GetWindow().GetSize().x, 0 }, {0.35 * Engine::GetWindow().GetSize().x, 0 } });
	AddGSComponent(cameraPtr);
	AddGSComponent(new Background());
	back = GetGSComponent<Background>();
	back->Add("Assets/Mode3_background.png", 1);

	cameraPtr->SetExtent({ { 0,0 }, { back->Size() - Engine::GetWindow().GetSize() } });
	playerPtr = new Player({ 100, Mode3::cloud_floor });
	gameObjectManager = new CS230::GameObjectManager;
	gameObjectManager->Add(playerPtr);
	gameObjectManager->Add(new Cloud({ 300, 300 }, 2));
	gameObjectManager->Add(new Cloud({ 3000, 300 }, 2));
	gameObjectManager->Add(new Cloud({ 600, 300 }, 1));
	AddGSComponent(gameObjectManager);
	//gameObjectManager->Add(new Bird({ 1000, cloud_floor }, { 674, 1132 }, playerPtr));
	//gameObjectManager->Add(new Bird({ 2000, cloud_floor }, { 1635, 2135 }, playerPtr));
	//gameObjectManager->Add(new Bird({ 3200, cloud_floor }, { 2860, 4250 }, playerPtr));
	//gameObjectManager->Add(new Bird({ 3800, cloud_floor }, { 2860, 4250 }, playerPtr));
	gameObjectManager->Add(new Exit({ {5550, static_cast<int>(Mode3::cloud_floor)}, {5760, 683} }));
	//gameObjectManager->Add(new EnemyShip(playerPtr));

	GameOverTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font2)).DrawTextToTexture("Game Over", 0xFFFFFFFF, true);
	RestartTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font2)).DrawTextToTexture("Press r to restart", 0xFFFFFFFF, true);

	std::string livesString = "Lives: " + std::to_string(lives);
	livesTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture(livesString, 0xFFFFFFFF, true);

	AddGSComponent(new Score(0, Fonts::Font1));
	AddGSComponent(new Timer(40));
	AddGSComponent(new Gravity(1875));
#ifdef _DEBUG
	AddGSComponent(new ShowCollision(CS230::InputKey::Keyboard::Tilde));
#endif
}

void Mode3::Update(double dt)
{
	GetGSComponent<CS230::Camera>()->Update(playerPtr->GetPosition());
#ifdef _DEBUG
	if (mainmenu.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
	}
	GetGSComponent<ShowCollision>()->Update(dt);
#else
	if (Reload.IsKeyReleased() == true && playerPtr->IsDead() == true)
	{
		Engine::GetGameStateManager().ReloadState();
	}
#endif
	if (Reload.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().ReloadState();
	}

	gameObjectManager->Update(dt);
	GetGSComponent<Timer>()->Update(dt);
	GetGSComponent<Score>()->Update(dt);

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
	if (playerPtr->IsDead() == true) {
		lives--;
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
}

void Mode3::Unload()
{
	ClearGSComponent();
	playerPtr = nullptr;
}

void Mode3::Draw()
{
	Engine::GetWindow().Clear(0x000000FF);
	CS230::Camera* cameraPtr = GetGSComponent<CS230::Camera>();
	GetGSComponent<Background>()->Draw(*cameraPtr);
	math::TransformMatrix cameraMatrix = cameraPtr->GetMatrix();
	gameObjectManager->DrawAll(cameraMatrix);
	math::ivec2 winSize = Engine::GetWindow().GetSize();
	GetGSComponent<Score>()->Draw(math::ivec2{ 10, winSize.y - 90 });
	livesTexture.Draw(math::TranslateMatrix(math::ivec2{ winSize.x * 2 / 5, winSize.y - livesTexture.GetSize().y - 5 }));
	GetGSComponent<Timer>()->Draw(math::ivec2{ winSize.x * 3 / 4, winSize.y - 90 });

	if (playerPtr->IsDead() == true)
	{
		RestartTexture.Draw(math::TranslateMatrix{ math::ivec2
			{Engine::GetWindow().GetSize().x / 2 - RestartTexture.GetSize().x / 2,winSize.y / 2 - GameOverTexture.GetSize().y } });
		GameOverTexture.Draw(math::TranslateMatrix{ math::ivec2
			{Engine::GetWindow().GetSize().x / 2 - GameOverTexture.GetSize().x / 2,winSize.y / 2 } });
	}
}