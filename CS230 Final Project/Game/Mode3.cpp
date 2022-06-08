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
#include "Mode2.h"
#include "Fonts.h"
#include "../Engine/ShowCollision.h"
#include "Laser.h"
#include "GameParticles.h"
#include "EnemyShip.h"
#include <doodle/doodle.hpp>

Mode3::Mode3() : mainmenu(CS230::InputKey::Keyboard::Escape), Reload(CS230::InputKey::Keyboard::R), camera(camera) {}

void Mode3::Load()
{
	gameObjectManager = new CS230::GameObjectManager;
	AddGSComponent(gameObjectManager);
	shipPtr = new Ship(math::vec2{ Engine::GetWindow().GetSize().x / 2.0, Engine::GetWindow().GetSize().y / 2.0 });
	gameObjectManager->Add(new Ship(math::vec2{ static_cast<double>(Engine::GetWindow().GetSize().x / 2),  static_cast<double>(Engine::GetWindow().GetSize().y / 2) }));
	gameObjectManager->Add(new Meteor());
	gameObjectManager->Add(new Meteor());
	gameObjectManager->Add(new Meteor());
	gameObjectManager->Add(new Meteor());
	gameObjectManager->Add(new Meteor());
	gameObjectManager->Add(shipPtr);
	gameObjectManager->Add(new EnemyShip(shipPtr));

	GameOverTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font2)).DrawTextToTexture("Game Over", 0xFFFFFFFF, true);
	RestartTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font2)).DrawTextToTexture("Press r to restart", 0xFFFFFFFF, true);

	AddGSComponent(new Score(0, Fonts::Font2));
	AddGSComponent(new HitEmitter());
	AddGSComponent(new MeteorBitEmitter());
#ifdef _DEBUG
	AddGSComponent(new ShowCollision(CS230::InputKey::Keyboard::Tilde));
#endif
}

void Mode3::Update(double dt)
{
#ifdef _DEBUG
	if (mainmenu.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
	}
	GetGSComponent<ShowCollision>()->Update(dt);
#else
	if (Reload.IsKeyReleased() == true && shipPtr->IsDead() == true)
	{
		Engine::GetGameStateManager().ReloadState();
	}
#endif
	if (Reload.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().ReloadState();
	}
	gameObjectManager->Update(dt);
	GetGSComponent<Score>()->Update(dt);
}

void Mode3::Unload()
{
	ClearGSComponent();
	shipPtr = nullptr;
}

void Mode3::Draw()
{
	Engine::GetWindow().Clear(0x000000FF);
	math::TransformMatrix camaraMatrix = camera.GetMatrix();
	gameObjectManager->DrawAll(camaraMatrix);

	math::ivec2 winSize = Engine::GetWindow().GetSize();
	GetGSComponent<Score>()->Draw((math::ivec2{ 10, winSize.y - 75 }));

	if (shipPtr->IsDead() == true)
	{
		RestartTexture.Draw(math::TranslateMatrix{ math::ivec2
			{Engine::GetWindow().GetSize().x / 2 - RestartTexture.GetSize().x / 2,winSize.y / 2 - GameOverTexture.GetSize().y } });
		GameOverTexture.Draw(math::TranslateMatrix{ math::ivec2
			{Engine::GetWindow().GetSize().x / 2 - GameOverTexture.GetSize().x / 2,winSize.y / 2 } });
	}
}