/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Floor.cpp
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022/5/23
-----------------------------------------------------------------*/
#include "Floor.h"
#include "../Engine/Rect.h"
#include "../Engine/Collision.h"

Floor::Floor(math::irect2 rect) : GameObject(static_cast<math::vec2>(rect.point1))
{
	AddGOComponent(new CS230::RectCollision({ math::ivec2{0,0},rect.Size() }, this));
}