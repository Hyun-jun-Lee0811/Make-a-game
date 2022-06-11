/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Assignment: CS230 Final Project
File Name: Ball.cpp
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022/4/16 spring
-----------------------------------------------------------------*/
#include "Ball.h"
#include "../Engine/Engine.h"
#include "Ball_Anims.h"
#include "../Engine/Collision.h"
#include "Gravity.h"
#include "../Engine/GameState.h"

Ball::Ball(math::vec2 startPos) : GameObject(startPos)
{
	AddGOComponent(new CS230::Sprite("Assets/Ball.spt", this));
	currState = &state_bounce;
	currState->Enter(this);
}

bool Ball::CanCollideWith(GameObjectType objectBType)
{
	if (objectBType == GameObjectType::Floor)
	{
		return true;
	}
	return false;
}

void Ball::ResolveCollision(GameObject* objectB)
{
	if (objectB->GetObjectType() == GameObjectType::Floor)
	{
		CS230::RectCollision* collideRect =
			static_cast<CS230::RectCollision*>(objectB->GetGOComponent<CS230::RectCollision>());
		SetPosition({ GetPosition().x, collideRect->GetWorldCoorRect().Top() });
		SetVelocity({ GetVelocity().x, 0 });
		ChangeState(&state_land);
	}
}

void Ball::State_Bounce::Enter(GameObject* object)
{
	Ball* ball = static_cast<Ball*>(object);
	ball->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ball_Anim::None_Anim));
	ball->GameObject::SetVelocity({ 0,bounceVelocity });
}

void Ball::State_Bounce::Update(GameObject* object, double dt)
{
	Ball* ball = static_cast<Ball*>(object);
	ball->GameObject::UpdateVelocity({ 0, -Engine::GetGSComponent<Gravity>()->GetValue() * dt });
}

void Ball::State_Bounce::TestForExit(GameObject* )
{
}

void Ball::State_Land::Enter(GameObject* object)
{
	Ball* ball = static_cast<Ball*>(object);
	ball->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ball_Anim::Squish_Anim));
}

void Ball::State_Land::Update(GameObject*, double) {}

void Ball::State_Land::TestForExit(GameObject* object)
{
	Ball* ball = static_cast<Ball*>(object);
	if (ball->GetGOComponent<CS230::Sprite>()->IsAnimationDone() == true)
	{
		ball->ChangeState(&ball->state_bounce);
	}
}