/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Assignment: CS230 Final Project
File Name: cammera2.cpp
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022 6/13 spring
-----------------------------------------------------------------*/
#include "Camera2.h"
#include "TransformMatrix.h"
#include "Collision.h"

CS230::Camera2::Camera2(math::rect2 movableRange) : movableRange(movableRange), position(position), extent(extent) {}

void CS230::Camera2::SetPosition(math::vec2 newPosition)
{
	position = newPosition;
}

const math::vec2& CS230::Camera2::GetPosition() const
{
	return position;
}

void CS230::Camera2::SetExtent(math::irect2 newExtent)
{
	extent = newExtent;
}

void CS230::Camera2::Update(const math::vec2& followObjPos)
{
	if (followObjPos.y < movableRange.Top() + position.y)
	{
		position.y = followObjPos.y - movableRange.Top();
	}
	else if (followObjPos.y > movableRange.Bottom() + position.y)
	{
		position.y = followObjPos.y - movableRange.Bottom() - 250;
	}


	if (position.x < extent.Left())
	{
		position.x = extent.Left();
	}
	else if (position.x > extent.Right())
	{
		position.x = extent.Right();
	}

	if (position.y < extent.Bottom())
	{
		position.y = extent.Bottom();
	}
	else if (position.y > extent.Top())
	{
		position.y = extent.Top();
	}
}

math::TranslateMatrix CS230::Camera2::GetMatrix()
{
	return math::TranslateMatrix(-position);
}