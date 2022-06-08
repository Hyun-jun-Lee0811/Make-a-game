/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: EnemyShip.h
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022/6/8
-----------------------------------------------------------------*/

#pragma once
#include "..\Engine\GameObject.h"
#include "..\Engine\Sprite.h"
#include "GameObjectTypes.h"

class EnemyShip : public CS230::GameObject
{
public:
	EnemyShip(GameObject* player);
	void Update(double dt);
	void Draw(math::TransformMatrix displayMatrix);

	GameObjectType GetObjectType() override
	{
		return GameObjectType::EnemyShip;
	}
	std::string GetObjectTypeName() override
	{
		return "EnemyShip";
	}

	bool CanCollideWith(GameObjectType collideAgainstType) override;
	void ResolveCollision(GameObject* collidedWith);

	bool IsDead() { return isDead; }
private:
	GameObject* player;
	CS230::Sprite flameLeft;
	CS230::Sprite flameRight;
	bool isDead;

	static constexpr double PI = 3.14;
	static constexpr double accel = 200;
	static constexpr double drag = 1;
	static constexpr double rotationRate = 3;
};