/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Player.h
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022/6/9
-----------------------------------------------------------------*/
#pragma once
#include "../Engine/Vec.h"
#include "../Engine/Sprite.h"
#include "../Engine/Input.h"
#include "../Engine/TransformMatrix.h"
#include "../Engine/GameObject.h"
#include "..\Engine\GameState.h"
#include "GameObjectTypes.h"
#include "Floor.h"

class Player : public CS230::GameObject
{
public:
	Player(math::vec2 startPos);
	void Update(double dt) override;
	void Draw(math::TransformMatrix displayMatrix);
	GameObjectType GetObjectType() override
	{
		return GameObjectType::Player;
	}
	std::string GetObjectTypeName() override
	{
		return "Player";
	}
	math::vec2 GetPosition();
	bool CanCollideWith(GameObjectType gameobjecttypeB) override;
	void ResolveCollision(GameObject* objectB) override;
	bool IsDead() { return isDead; }

private:
	math::vec2 startPos;

	static constexpr double jumpVelocity = 1200;
	static constexpr double xAccel = 500;
	static constexpr double xDrag = 750;
	static constexpr double maxXVelocity = 750;
	CS230::InputKey jumpKey;
	CS230::InputKey moveLeftKey;
	CS230::InputKey moveRightKey;
	GameObject* objectD;

	static constexpr double hurtTime = 2;
	double Playertimer;
	bool drawPlayer;

	bool isDead;
	GameObject* standingOnObject;

	class State_Idle : public State
	{
	public:
		virtual void Enter(GameObject* object) override;
		virtual void Update(GameObject* object, double dt) override;
		virtual void TestForExit(GameObject* object) override;
		std::string GetName() override { return "Idle"; }
	};
	class State_Running : public State
	{
	public:
		virtual void Enter(GameObject* object) override;
		virtual void Update(GameObject* object, double dt) override;
		virtual void TestForExit(GameObject* object) override;
		std::string GetName() override { return "Running"; }
	};
	class State_Skidding : public State
	{
	public:
		virtual void Enter(GameObject* object) override;
		virtual void Update(GameObject* object, double dt) override;
		virtual void TestForExit(GameObject* object) override;
		std::string GetName() override { return "Skidding"; }
	};
	class State_Jumping : public State
	{
	public:
		virtual void Enter(GameObject* object) override;
		virtual void Update(GameObject* object, double dt) override;
		virtual void TestForExit(GameObject* object) override;
		std::string GetName() override { return "Jumping"; }
	};
	class State_Falling : public State
	{
	public:
		virtual void Enter(GameObject* object) override;
		virtual void Update(GameObject* object, double dt) override;
		virtual void TestForExit(GameObject* object) override;
		std::string GetName() override { return "Falling"; }
	};
	State_Idle stateIdle;
	State_Running stateRunning;
	State_Skidding stateSkidding;
	State_Jumping stateJumping;
	State_Falling stateFalling;

	void UpdateXVelocity(double dt);
};