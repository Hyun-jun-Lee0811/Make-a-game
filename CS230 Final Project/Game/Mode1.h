/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Assignment: CS230 Final Project
File Name: Mode1.h
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022/4/16 Spring
-----------------------------------------------------------------*/
#pragma once
#include "../Engine/Rect.h"
#include "..\Engine\GameState.h"
#include "..\Engine\Input.h"
#include "Background.h"
#include "../Engine/TransformMatrix.h"
#include "../Engine/GameObjectManager.h"
#include "../Engine/Camera.h"
#include "TreeStump.h"
#include "Bunny.h"


class Hero;

class Mode1 : public CS230::GameState
{
public:
	double gravity = 1875;
	Mode1();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;

	std::string GetName() override { return "Mode1"; }

private:
	static constexpr double floor = 126.0f;
	Background* back;
	CS230::InputKey mainmenu;
	CS230::InputKey Reload;
	CS230::GameObjectManager* gameObjectManager;
	Hero* heroPtr;

	int lives;

	CS230::Texture livesTexture;
};