/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Assignment: CS230 Final Project
File Name: Ship.h
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022/4/16
-----------------------------------------------------------------*/
#pragma once
#include "../Engine/Vec.h"
#include "../Engine/Sprite.h"
#include "../Engine/Input.h"
#include "../Engine/Texture.h"
#include "../Engine/TransformMatrix.h"
#include "../Engine/GameObject.h"
#include "GameObjectTypes.h"

class Ship : public CS230::GameObject
{
public:
	Ship(math::vec2 startPos);
	void Update(double dt) override;
	void Draw(math::TransformMatrix displayMatrix) override;
	GameObjectType GetObjectType() override
	{
		return GameObjectType::Ship;
	}
	std::string GetObjectTypeName() override
	{
		return "Ship";
	}
	bool CanCollideWith(GameObjectType objectBType) override;
	void ResolveCollision(CS230::GameObject* objectB) override;
	bool IsDead() { return isDead; }

private:
	math::vec2 startPos;
	math::vec2 scale;
	CS230::Sprite leftSprtie;
	CS230::Sprite rightSprite;
	static constexpr double accel = 400.0;
	static constexpr double drag = 1.0;
	bool run;
	static constexpr double max_v = 500.0;
	CS230::InputKey rotateCounterKey;
	CS230::InputKey rotateClockKey;
	CS230::InputKey accelerateKey;
	CS230::InputKey SlowDown;
	CS230::InputKey Shoot;

	double currentRotation = 0.0;
	double speed = 2.0;
	bool isDead;
};