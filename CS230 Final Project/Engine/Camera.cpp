/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: cammera.cpp
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022 4/16 spring
-----------------------------------------------------------------*/
#include "Camera.h"
#include "TransformMatrix.h"
#include "Collision.h"

CS230::Camera::Camera(math::rect2 movableRange) : movableRange(movableRange), position(position), extent(extent) {}

void CS230::Camera::SetPosition(math::vec2 newPosition)
{
	position = newPosition;
}

const math::vec2& CS230::Camera::GetPosition() const
{
	return position;
}

void CS230::Camera::SetExtent(math::irect2 newExtent)
{
	extent = newExtent;
}

void CS230::Camera::Update(const math::vec2& followObjPos)
{

	if (followObjPos.x < movableRange.Left() + position.x)
	{
		position.x = followObjPos.x - movableRange.Left();
	}
	else if (followObjPos.x > movableRange.Right() + position.x)
	{
		position.x = followObjPos.x - movableRange.Right();
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

math::TranslateMatrix CS230::Camera::GetMatrix()
{
	return math::TranslateMatrix(-position);
}