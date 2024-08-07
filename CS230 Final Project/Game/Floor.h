/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Assignment: CS230 Final Project
File Name: Floor.h
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022/5/23
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"

namespace math
{
	struct irect2;
}

class Floor : public CS230::GameObject
{
public:
	Floor(math::irect2 rect);
	std::string GetObjectTypeName() override { return "Floor"; }
	virtual GameObjectType GetObjectType() override { return GameObjectType::Floor; }
private:
};