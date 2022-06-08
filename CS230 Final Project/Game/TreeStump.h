/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: TreeStump.h
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022/4/30 spring
-----------------------------------------------------------------*/
#pragma once
#include "../Engine/GameObject.h"
#include "GameObjectTypes.h"

class TreeStump : public CS230::GameObject
{
public:
	TreeStump(math::vec2 pos, int size);
    GameObjectType GetObjectType() override
    {
        return GameObjectType::TreeStump;
    }
    std::string GetObjectTypeName() override
    {
        return "TreeStump";
    }
private:
};