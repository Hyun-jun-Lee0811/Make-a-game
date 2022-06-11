/*-------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Assignment: CS230 Final Project
File Name: Laser.cpp
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022/5/24
-----------------------------------------------------------------*/
#include "Laser.h"
#include "GameObjectTypes.h"
#include "..\Engine\Engine.h"
#include "..\Engine\GameObject.h"

Laser::Laser(math::vec2 pos, double rotation, math::vec2 scale, math::vec2 laserVelocity)
	:GameObject(pos, rotation, scale)
{
	SetVelocity(laserVelocity);
	AddGOComponent(new CS230::Sprite("Assets/Laser.spt", this));
}

void Laser::Update(double dt)
{
	GameObject::Update(dt);
	const math::vec2 WindowSize = math::vec2{ Engine::GetWindow().GetSize() };
	const math::vec2 ScreenSize = math::vec2{ GetGOComponent<CS230::Sprite>()->GetFrameSize() / 2 };

	if (GetPosition().x + ScreenSize.x < 0)
	{
		destroy();
		return;
	}
	else if (GetPosition().x - ScreenSize.x > WindowSize.x)
	{
		destroy();
		return;
	}
	else if (GetPosition().y - ScreenSize.y > WindowSize.y)
	{
		destroy();
		return;
	}
	else if (GetPosition().y + ScreenSize.y < 0)
	{
		destroy();
		return;
	}
}

bool Laser::CanCollideWith(GameObjectType objectBType)
{
	if (objectBType == GameObjectType::Meteor)
	{
		return true;
	}
	if (objectBType == GameObjectType::EnemyShip)
	{
		return true;
	}
	return false;
}

void Laser::ResolveCollision(GameObject* objectB)
{
	destroy_check();
	objectB->ResolveCollision(this);
}