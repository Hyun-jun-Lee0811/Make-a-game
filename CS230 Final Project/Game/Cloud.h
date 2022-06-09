/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Cloud.h
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022/6/9
-----------------------------------------------------------------*/
#pragma once

#include "../Engine/GameObject.h"
#include "GameObjectTypes.h"

class Cloud : public CS230::GameObject
{
public:
    Cloud(math::vec2 pos, int size);
    GameObjectType GetObjectType() override
    {
        return GameObjectType::Cloud;
    }
    std::string GetObjectTypeName() override
    {
        return "Cloud";
    }
private:
};