/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Assignment: CS230 Final Project
File Name: LightningCloud.h
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022/6/11
-----------------------------------------------------------------*/
#pragma once
#include "../Engine/GameObject.h"
#include "GameObjectTypes.h"

class LightningCloud : public CS230::GameObject
{
public:
	LightningCloud(math::vec2 startPos);
	GameObjectType GetObjectType() override
	{
		return GameObjectType::LightningCloud;
	}
	std::string GetObjectTypeName() override
	{
		return "LightningCloud";
	}

private:
};