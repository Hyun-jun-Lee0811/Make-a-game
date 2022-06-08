/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Hero.cpp
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022/4/16 spring
-----------------------------------------------------------------*/
#include "Hero.h"
#include "../Engine/Engine.h"
#include "../Engine/Camera.h"
#include "Mode1.h"
#include "Hero_Anims.h"
#include "../Engine/Collision.h"
#include "Gravity.h"
#include "GameParticles.h"

Hero::Hero(math::vec2 startPos) : GameObject(startPos), jumpKey(CS230::InputKey::Keyboard::Up),
moveLeftKey(CS230::InputKey::Keyboard::Left), moveRightKey(CS230::InputKey::Keyboard::Right), hurtTimer(0), drawHero(true), isDead(false)
{
	AddGOComponent(new CS230::Sprite("Assets/Hero.spt", this));
	currState = &stateIdle;
	currState->Enter(this);
	standingOnObject = this;
}

void Hero::Update(double dt)
{
	GameObject::Update(dt);
	if (GetPosition().x <= (GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect().Size().x / 2))
	{
		SetPosition(math::vec2{ GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect().Size().x / 2 ,GetPosition().y });
		SetVelocity({ 0,GetVelocity().y });
	}
	else if (GetPosition().x + GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect().Size().x / 2 >= Engine::GetGSComponent<CS230::Camera>()->GetPosition().x + Engine::GetWindow().GetSize().x)
	{
		SetPosition({ Engine::GetGSComponent<CS230::Camera>()->GetPosition().x + Engine::GetWindow().GetSize().x - GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2,GetPosition().y });
		SetVelocity({ 0,GetVelocity().y });
	}

	if (hurtTimer != 0)
	{
		drawHero = !drawHero;
		hurtTimer -= dt;
		if (hurtTimer < 0)
		{
			drawHero = true;
			hurtTimer = 0;
		}
	}
}

void Hero::Draw(math::TransformMatrix displayMatrix)
{
	if (drawHero == true)
	{
		GameObject::Draw(displayMatrix);
	}
}

math::vec2 Hero::GetPosition()
{
	return GameObject::GetPosition();
}

bool Hero::CanCollideWith(GameObjectType gameobjecttypeB)
{
	if (gameobjecttypeB == GameObjectType::Particle)
	{
		return false;
	}
	return true;
}

void Hero::ResolveCollision(GameObject* objectB)
{
	math::rect2 collideRect = objectB->GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect();
	math::rect2 heroRect = GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect();

	switch (objectB->GetObjectType())
	{
	case GameObjectType::Ball:
		if (currState == &stateFalling)
		{
			if (collideRect.Bottom() < GetPosition().y)
			{
				SetVelocity({ GetVelocity().x, jumpVelocity });
				return;
			}
		}
		if (GetPosition().x < objectB->GetPosition().x)
		{
			SetPosition(math::vec2{ GetPosition().x - (heroRect.Right() - collideRect.Left()),GetPosition().y });
			currState = &stateFalling;
			SetVelocity(math::vec2{ -maxXVelocity / 2,jumpVelocity } / 2);
			hurtTimer = hurtTime;
		}
		if (GetPosition().x > objectB->GetPosition().x)
		{
			SetPosition(math::vec2{ GetPosition().x + (collideRect.Right() - heroRect.Left()),GetPosition().y });
			currState = &stateFalling;
			SetVelocity(math::vec2{ maxXVelocity / 2 ,jumpVelocity / 2 });
			hurtTimer = hurtTime;
		}
		break;
	case GameObjectType::Bunny:
		if (currState == &stateSkidding)
		{
			if (GetVelocity().x > collideRect.Left() || GetVelocity().x < collideRect.Right())
			{
				objectB->ResolveCollision(this);
				return;
			}
		}
		if (currState == &stateFalling)
		{
			if (GetPosition().y > collideRect.Bottom())
			{
				SetVelocity({ GetVelocity().x, jumpVelocity / 2 });
				objectB->ResolveCollision(this);
				if (GetVelocity().x < 0)
				{
					Engine::GetGameStateManager().GetGSComponent<SmokeEmitter>()->Emit(1, math::vec2{ (collideRect.Right() + heroRect.Left()) / 2, (collideRect.Top() + heroRect.Bottom()) / 2 }
					, { 0, 0 }, { 0,0 }, 0);
				}
				else
				{
					Engine::GetGameStateManager().GetGSComponent<SmokeEmitter>()->Emit(1, math::vec2{ (collideRect.Left() + heroRect.Right()) / 2, (collideRect.Top() + heroRect.Bottom()) / 2 }
					, { 0, 0 }, { 0,0 }, 0);
				}
				return;
			}
		}
		if (GetPosition().x > objectB->GetPosition().x)
		{
			SetVelocity(math::vec2{ maxXVelocity / 2 ,jumpVelocity / 2 });
			currState = &stateFalling;
			SetPosition(math::vec2{ GetPosition().x + (collideRect.Right() - heroRect.Left()),GetPosition().y });
			hurtTimer = hurtTime;
		}
		if (GetPosition().x < objectB->GetPosition().x)
		{
			SetVelocity(math::vec2{ -maxXVelocity / 2,jumpVelocity } / 2);
			currState = &stateFalling;
			SetPosition(math::vec2{ GetPosition().x - (heroRect.Right() - collideRect.Left()),GetPosition().y });
			hurtTimer = hurtTime;
		}
		break;
	case GameObjectType::Floor: [[fallthrough]];
	case GameObjectType::TreeStump:
		if (currState == &stateFalling) {
			if (heroRect.Top() > collideRect.Top() && objectB->DoesCollideWith(GetPosition()))
			{
				SetPosition({ GetPosition().x, collideRect.Top() });
				standingOnObject = objectB;
				if (GetVelocity().y < -jumpVelocity)
				{
					Engine::GetGameStateManager().GetGSComponent<SmokeEmitter>()->Emit(1, GetPosition(), { 0, 0 }, { 0,0 }, 0);
				}
				currState->TestForExit(this);
				return;
			}
		}
		if (GetPosition().x > objectB->GetPosition().x)
		{
			SetPosition(math::vec2{ collideRect.Right() + heroRect.Size().x / 2,GetPosition().y });
			SetVelocity(math::vec2{ 0,GetVelocity().y });
		}
		else
		{
			SetPosition(math::vec2{ collideRect.Left() - heroRect.Size().x / 2 ,GetPosition().y });
			SetVelocity(math::vec2{ 0,GetVelocity().y });
		}
		break;
	case GameObjectType::Trigger:
		objectB->ResolveCollision(this);
		break;
	}
}

void Hero::UpdateXVelocity(double dt)
{
	if (moveLeftKey.IsKeyDown() == true)
	{
		GameObject::UpdateVelocity({ -xAccel * dt , 0 });
		if (GetVelocity().x < -maxXVelocity)
		{
			GameObject::SetVelocity({ -maxXVelocity, GameObject::GetVelocity().y });
		}
	}
	else if (moveRightKey.IsKeyDown() == true)
	{
		GameObject::UpdateVelocity({ xAccel * dt , 0 });
		if (GameObject::GetVelocity().x > maxXVelocity)
		{
			GameObject::SetVelocity({ maxXVelocity, GameObject::GetVelocity().y });
		}
	}
	else
	{
		double xDragDt = xDrag * dt;
		if (GameObject::GetVelocity().x > xDragDt)
		{
			GameObject::UpdateVelocity({ -xDragDt, 0 });
		}
		else if (GameObject::GetVelocity().x < -xDragDt)
		{
			GameObject::UpdateVelocity({ xDragDt, 0 });
		}
		else
		{
			GameObject::SetVelocity({ 0, GameObject::GetVelocity().y });
		}
	}
}

void Hero::State_Idle::Enter(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Hero_Anim::Hero_Idle_Anim));
	if (hero->standingOnObject == nullptr)
	{
		Engine::GetLogger().LogError("Error!!");
	}
}

void Hero::State_Idle::Update(GameObject*, double) {}

void Hero::State_Idle::TestForExit(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	if (hero->moveLeftKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateRunning);
	}
	if (hero->moveRightKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateRunning);
	}
	if (hero->jumpKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateJumping);
	}
}

void Hero::State_Running::Enter(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Hero_Anim::Hero_Run_Anim));

	if (hero->standingOnObject == nullptr)
	{
		Engine::GetLogger().LogError("Error!!");
	}
	if (hero->moveLeftKey.IsKeyDown() == true)
	{
		hero->SetScale({ math::vec2{-1.0,1.0} });
	}
	if (hero->moveRightKey.IsKeyDown() == true)
	{
		hero->SetScale({ math::vec2{1.0,1.0} });
	}
}

void Hero::State_Running::Update(GameObject* object, double dt)
{
	Hero* hero = static_cast<Hero*>(object);
	hero->UpdateXVelocity(dt);
}

void Hero::State_Running::TestForExit(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	if (hero->moveLeftKey.IsKeyDown() == true && hero->GetVelocity().x > 0)
	{
		hero->ChangeState(&hero->stateSkidding);
	}
	if (hero->moveRightKey.IsKeyDown() == true && hero->GetVelocity().x < 0)
	{
		hero->ChangeState(&hero->stateSkidding);
	}
	if (hero->GetVelocity().x == 0)
	{
		hero->ChangeState(&hero->stateIdle);
	}
	if (hero->jumpKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateJumping);
	}
	if (hero->standingOnObject != nullptr && hero->standingOnObject->DoesCollideWith(hero->GetPosition()) == false)
	{
		hero->standingOnObject = nullptr;
		hero->ChangeState(&hero->stateFalling);
	}
}

void Hero::State_Skidding::Enter(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Hero_Anim::Hero_Fall_Anim));
}

void Hero::State_Skidding::Update(GameObject* object, double dt)
{
	Hero* hero = static_cast<Hero*>(object);
	hero->UpdateXVelocity(dt);
}

void Hero::State_Skidding::TestForExit(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	if (hero->jumpKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateJumping);
	}

	if (hero->moveLeftKey.IsKeyDown() == true)
	{
		if (hero->GameObject::GetVelocity().x <= 0)
		{
			hero->ChangeState(&hero->stateRunning);
		}
	}
	else if (hero->moveRightKey.IsKeyDown() == true)
	{
		if (hero->GameObject::GetVelocity().x >= 0)
		{
			hero->ChangeState(&hero->stateRunning);
		}
	}
	else if (hero->moveLeftKey.IsKeyDown() == false && hero->moveRightKey.IsKeyDown() == false)
	{
		hero->ChangeState(&hero->stateRunning);
	}
}

void Hero::State_Jumping::Enter(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Hero_Anim::Hero_Jump_Anim));
	hero->GameObject::SetVelocity({ hero->GameObject::GetVelocity().x , Hero::jumpVelocity });
	hero->standingOnObject = nullptr;
}

void Hero::State_Jumping::Update(GameObject* object, double dt)
{
	Hero* hero = static_cast<Hero*>(object);
	hero->UpdateVelocity({ 0, -Engine::GetGSComponent<Gravity>()->GetValue() * dt });
	hero->UpdateXVelocity(dt);
}

void Hero::State_Jumping::TestForExit(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	if (hero->jumpKey.IsKeyDown() == false)
	{
		hero->ChangeState(&hero->stateFalling);
		hero->GameObject::SetVelocity({ hero->GameObject::GetVelocity().x , 0 });
	}
	else if (hero->GameObject::GetVelocity().y <= 0)
	{
		hero->ChangeState(&hero->stateFalling);
	}
}

void Hero::State_Falling::Enter(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Hero_Anim::Hero_Fall_Anim));
}

void Hero::State_Falling::Update(GameObject* object, double dt)
{
	Hero* hero = static_cast<Hero*>(object);
	hero->GameObject::UpdateVelocity({ 0,-Engine::GetGSComponent<Gravity>()->GetValue() * dt });
	hero->UpdateXVelocity(dt);
}

void Hero::State_Falling::TestForExit(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	if (hero->standingOnObject != nullptr)
	{
		if (hero->GameObject::GetVelocity().x > 0)
		{
			if (hero->moveLeftKey.IsKeyDown() == true)
			{
				hero->ChangeState(&hero->stateSkidding);
			}
			else
			{
				hero->ChangeState(&hero->stateRunning);
			}
		}
		else if (hero->GameObject::GetVelocity().x <= 0)
		{
			if (hero->moveRightKey.IsKeyDown() == true)
			{
				hero->ChangeState(&hero->stateSkidding);
			}
			else
			{
				hero->ChangeState(&hero->stateRunning);
			}
		}
		else
		{
			hero->ChangeState(&hero->stateIdle);
		}
		hero->GameObject::SetVelocity({ hero->GameObject::GetVelocity().x , 0 });
	}
	if (hero->GetPosition().y < -300)
	{
		hero->isDead = true;
	}
}