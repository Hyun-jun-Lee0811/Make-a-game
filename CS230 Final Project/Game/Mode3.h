/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Mode3.h
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022/6/9
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\GameState.h"
#include "..\Engine\Input.h"
#include "ship.h"
#include "../Engine/GameObjectManager.h"
#include "Meteor.h"
#include "..\Engine\Camera.h"
#include "Score.h"

class Mode3 : public CS230::GameState
{
public:
	Mode3();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;

	std::string GetName() override { return "Mode3"; }
private:
	CS230::InputKey mainmenu;
	CS230::InputKey Reload;
	CS230::Camera camera;
	CS230::GameObjectManager* gameObjectManager;

	Ship* shipPtr;
	CS230::Texture GameOverTexture;
	CS230::Texture RestartTexture;
};