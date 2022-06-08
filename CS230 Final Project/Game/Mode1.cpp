/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Mode1.cpp
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022/4/16 Spring
-----------------------------------------------------------------*/
#include "Mode1.h"
#include "../Engine/Engine.h"
#include "Screens.h"
#include "Fonts.h"
#include "../Engine/ShowCollision.h"
#include "Timer.h"
#include "Score.h"
#include "Floor.h"
#include "Exit.h"
#include "Gravity.h"
#include "GameParticles.h"

Mode1::Mode1() : mainmenu(CS230::InputKey::Keyboard::Escape), Reload(CS230::InputKey::Keyboard::R), heroPtr(nullptr), lives(3), back(nullptr), gameObjectManager(nullptr) {}

void Mode1::Load()
{
	CS230::Camera* cameraPtr = new CS230::Camera({ { 0.15 * Engine::GetWindow().GetSize().x, 0 }, {0.35 * Engine::GetWindow().GetSize().x, 0 } });
	AddGSComponent(cameraPtr);
	AddGSComponent(new Background());
	back = GetGSComponent<Background>();
	back->Add("Assets/clouds.png", 4);
	back->Add("Assets/Mountains.png", 2);
	back->Add("Assets/foreground.png", 1);

	cameraPtr->SetExtent({ { 0,0 }, { back->Size() - Engine::GetWindow().GetSize() } });
	heroPtr = new Hero({ 100, Mode1::floor });
	gameObjectManager = new CS230::GameObjectManager;
	AddGSComponent(gameObjectManager);

	gameObjectManager->Add(new Ball({ 600, Mode1::floor }));
	gameObjectManager->Add(new Ball({ 2700, Mode1::floor }));
	gameObjectManager->Add(new Ball({ 4800, Mode1::floor }));
	gameObjectManager->Add(new Bunny({ 1000, floor }, { 674, 1132 }, heroPtr));
	gameObjectManager->Add(new Bunny({ 2000, floor }, { 1635, 2135 }, heroPtr));
	gameObjectManager->Add(new Bunny({ 3200, floor }, { 2860, 4250 }, heroPtr));
	gameObjectManager->Add(new Bunny({ 3800, floor }, { 2860, 4250 }, heroPtr));
	gameObjectManager->Add(new TreeStump({ 300, Mode1::floor }, 3));
	gameObjectManager->Add(new TreeStump({ 1200, Mode1::floor }, 2));
	gameObjectManager->Add(new TreeStump({ 2200, Mode1::floor }, 1));
	gameObjectManager->Add(new TreeStump({ 2800, Mode1::floor }, 5));
	gameObjectManager->Add(new TreeStump({ 5100, Mode1::floor }, 5));
	gameObjectManager->Add(new Floor({ {0, 0}, {1471, static_cast<int>(Mode1::floor)} }));
	gameObjectManager->Add(new Floor({ {1602, 0}, {4262, static_cast<int>(Mode1::floor)} }));
	gameObjectManager->Add(new Floor({ {4551, 0}, {5760, static_cast<int>(Mode1::floor)} }));
	gameObjectManager->Add(new Exit({ {5550, static_cast<int>(Mode1::floor)}, {5760, 683} }));
	gameObjectManager->Add(heroPtr);

	GetGSComponent<CS230::Camera>()->SetPosition(math::vec2{ 0, 0 });
	GetGSComponent<CS230::Camera>()->SetExtent(math::irect2{ math::ivec2{0, 0}, math::ivec2{back->Size().x - Engine::GetWindow().GetSize().x,back->Size().y} });

	std::string livesString = "Lives: " + std::to_string(lives);
	livesTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture(livesString, 0xFFFFFFFF, true);

	AddGSComponent(new Score(0, Fonts::Font1));
	AddGSComponent(new Timer(60));
	AddGSComponent(new Gravity(1875));
	AddGSComponent(new SmokeEmitter());
#ifdef _DEBUG
	AddGSComponent(new ShowCollision(CS230::InputKey::Keyboard::Tilde));
#endif
}

void Mode1::Update(double dt)
{
	gameObjectManager->Update(dt);
	GetGSComponent<CS230::Camera>()->Update(heroPtr->GetPosition());
	if (mainmenu.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
	}
	if (Reload.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().ReloadState();
	}

	GetGSComponent<ShowCollision>()->Update(dt);
	GetGSComponent<Timer>()->Update(dt);
	GetGSComponent<Score>()->Update(dt);

	if (GetGSComponent<Timer>()->hasEnded())
	{
		lives -= 1;
		if (lives <= 0)
		{
			lives = 3;
			Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
		}
		else
		{
			Engine::GetGameStateManager().ReloadState();
		}
	}
	if (heroPtr->IsDead() == true) {
		lives--;
		if (lives <= 0)
		{
			lives = 3;
			Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
		}
		else
		{
			Engine::GetGameStateManager().ReloadState();
		}
	}
}

void Mode1::Unload()
{
	ClearGSComponent();
	heroPtr = nullptr;
}

void Mode1::Draw()
{
	Engine::GetWindow().Clear(0x0000FFFF);
	CS230::Camera* cameraPtr = GetGSComponent<CS230::Camera>();
	GetGSComponent<Background>()->Draw(*cameraPtr);
	math::TransformMatrix cameraMatrix = cameraPtr->GetMatrix();
	gameObjectManager->DrawAll(cameraMatrix);
	math::ivec2 winSize = Engine::GetWindow().GetSize();
	GetGSComponent<Score>()->Draw(math::ivec2{ 10, winSize.y - 90 });
	livesTexture.Draw(math::TranslateMatrix(math::ivec2{ winSize.x * 2 / 5, winSize.y - livesTexture.GetSize().y - 5 }));
	GetGSComponent<Timer>()->Draw(math::ivec2{ winSize.x * 3 / 4, winSize.y - 90 });
}