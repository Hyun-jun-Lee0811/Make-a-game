/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Assignment: CS230 Final Project
File Name: Bird.h
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022/6/9
-----------------------------------------------------------------*/
#pragma once
#include "../Engine/GameObject.h"
#include "GameObjectTypes.h"
#include "Player.h"

class Bird : public CS230::GameObject
{
public:
	Bird(math::vec2 pos, std::vector<double> patrolNodes, Player* playerPtr);
	GameObjectType GetObjectType() override
	{
		return GameObjectType::Bird;
	}
	std::string GetObjectTypeName() override
	{
		return "Bird";
	}
	void ResolveCollision(GameObject* objectC) override;
private:
	class Bird_State_Patrol : public State
	{
	public:
		void Enter(GameObject* object) override;
		void Update(GameObject* object, double dt) override;
		void TestForExit(GameObject* object) override;
		//void TestForExit(GameObject* object) override;
		std::string GetName() override { return "bounce"; }
	};
	class Bird_State_Attack : public State
	{
	public:
		void Enter(GameObject* object) override;
		void Update(GameObject* object, double dt) override;
		void TestForExit(GameObject* object) override;
		std::string GetName() override { return "attack"; }
	};
	class Bird_State_Dead : public State
	{
	public:
		void Enter(GameObject* object) override;
		void Update(GameObject* object, double dt) override;
		void TestForExit(GameObject* object) override;
		std::string GetName() override { return "land"; }
	};
	Bird_State_Patrol statePatrol;
	Bird_State_Attack stateAttack;
	Bird_State_Dead stateDead;
	Player* playerPtr;

	std::vector<double> patrolNodes;
	int currPatrolNode;
	static constexpr int velocity = 75;
};