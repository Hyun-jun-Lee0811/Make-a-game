/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Assignment: CS230 Final Project
File Name: Ball.h
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022/4/16 spring
-----------------------------------------------------------------*/
#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Camera.h"
#include "GameObjectTypes.h"

namespace math { struct vec2; }

class Ball : public CS230::GameObject
{
public:
	Ball(math::vec2 startPos);
	GameObjectType GetObjectType() override
	{
		return GameObjectType::Ball;
	}
	std::string GetObjectTypeName() override
	{
		return "Ball";
	}

	bool CanCollideWith(GameObjectType objectBType) override;
	void ResolveCollision(GameObject* objectB) override;

private:
	math::vec2 startPos;

	static constexpr double bounceVelocity = 700;

	class State_Bounce : public State
	{
	public:
		virtual void Enter(GameObject* object) override;
		virtual void Update(GameObject* object, double dt) override;
		virtual void TestForExit(GameObject* object) override;
		std::string GetName() override { return "Bounce"; }
	};

	class State_Land : public State
	{
	public:
		virtual void Enter(GameObject* object) override;
		virtual void Update(GameObject* object, double dt) override;
		virtual void TestForExit(GameObject* object) override;
		std::string GetName() override { return "squish"; }
	};
	State_Bounce state_bounce;
	State_Land state_land;

	//void UpdateXVelocity(double dt);
};