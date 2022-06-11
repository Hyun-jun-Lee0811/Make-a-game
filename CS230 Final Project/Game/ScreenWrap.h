/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Assignment: CS230 Final Project
File Name: ScreenWrap.h
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022/5/10
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\Component.h" 
#include "../Engine/GameObject.h"

class CS230::GameObject;

class ScreenWrap : public CS230::Component
{
public:
	ScreenWrap(CS230::GameObject& object) : object(object) {}
	void Update(double dt) override;
private:
	CS230::GameObject& object;
};