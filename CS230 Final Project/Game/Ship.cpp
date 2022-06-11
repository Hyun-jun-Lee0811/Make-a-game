/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Assignment: CS230 Final Project
File Name: Ship.cpp
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022 4/16 spring
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"
#include "Ship.h"
#include "Flame_Anims.h"
#include "ScreenWrap.h"
#include "../Engine/Collision.h"
#include "../Engine/ShowCollision.h"
#include "Ship_Anims.h"
#include "Laser.h"
#include "../Engine/GameObjectManager.h"

Ship::Ship(math::vec2 startPos) : GameObject(startPos, GameObject::GetRotation(), GameObject::GetScale()), rotateCounterKey(CS230::InputKey::Keyboard::A), rotateClockKey(CS230::InputKey::Keyboard::D),
accelerateKey(CS230::InputKey::Keyboard::W), SlowDown(CS230::InputKey::Keyboard::S), run(true),
leftSprtie("Assets/flame.spt", this), rightSprite("Assets/flame.spt", this), isDead(false), Shoot(CS230::InputKey::Keyboard::Space)
{
	AddGOComponent(new CS230::Sprite("Assets/Ship.spt", this));
	AddGOComponent(new ScreenWrap(*this));
}

void Ship::Update(double dt)
{
	if (isDead == false && accelerateKey.IsKeyDown() == true)
	{
		UpdateVelocity(math::RotateMatrix(GetRotation()) * math::vec2{ 0,accel * dt });
		if (run == false)
		{
			leftSprtie.PlayAnimation(static_cast<int>(Flame_Anim::Flame_Anim));
			rightSprite.PlayAnimation(static_cast<int>(Flame_Anim::Flame_Anim));
			run = true;
		}
	}
	else
	{
		if (isDead == false && run == true)
		{
			leftSprtie.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
			rightSprite.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
			run = false;
		}
	}
	if (isDead == false && GetVelocity().y >= max_v)
	{
		SetVelocity({ GetVelocity().x,max_v });
	}
	if (isDead == false && GetVelocity().x <= -max_v)
	{
		SetVelocity({ GetVelocity().x,-max_v });
	}

	if (isDead == false && rotateCounterKey.IsKeyDown() == true)
	{
		UpdateRotation({ speed * dt });
	}
	if (isDead == false && rotateClockKey.IsKeyDown() == true)
	{
		UpdateRotation({ -speed * dt });
	}

	if (Shoot.IsKeyDown() == true)
	{
		Engine::GetGSComponent<CS230::GameObjectManager>()->Add(
			new Laser(GetMatrix() * static_cast<math::vec2>(GetGOComponent<CS230::Sprite>()->GetHotSpot(3)),
				GetRotation(), GetScale(), math::RotateMatrix(GetRotation()) * Laser::LaserVelocity));
		Engine::GetGSComponent<CS230::GameObjectManager>()->Add(
			new Laser(GetMatrix() * static_cast<math::vec2>(GetGOComponent<CS230::Sprite>()->GetHotSpot(4)),
				GetRotation(), GetScale(), math::RotateMatrix(GetRotation()) * Laser::LaserVelocity));
	}

	GameObject::UpdateVelocity({ -(GameObject::GetVelocity() * Ship::drag * dt) });
	GameObject::UpdatePosition({ GameObject::GetVelocity() * dt });
	SetScale({ 0.75,0.75 });
	GetGOComponent < ScreenWrap >()->Update(dt);
	GetGOComponent<CS230::Sprite>()->Update(dt);
}

void Ship::Draw(math::TransformMatrix displayMatrix)
{
	GetGOComponent<CS230::Sprite>()->Draw(GetMatrix());
	leftSprtie.Draw(GetMatrix() * math::TranslateMatrix(GetGOComponent<CS230::Sprite>()->GetHotSpot(1)));
	rightSprite.Draw(GetMatrix() * math::TranslateMatrix(GetGOComponent<CS230::Sprite>()->GetHotSpot(2)));
	ShowCollision* showCollisionPtr = Engine::GetGSComponent<ShowCollision>();
	if (showCollisionPtr != nullptr && showCollisionPtr->IsEnabled() == true)
	{
		CS230::Collision* collisionPtr = GetGOComponent<CS230::Collision>();
		if (collisionPtr != nullptr)
		{
			collisionPtr->Draw(displayMatrix);
		}
	}
}

bool Ship::CanCollideWith(GameObjectType objectBType)
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

void Ship::ResolveCollision(CS230::GameObject* objectB)
{
	if (isDead == true)
	{
		RemoveGOComponent<CS230::Collision>();
		leftSprtie.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
		rightSprite.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
	}
	if (objectB->GetObjectType() == GameObjectType::Meteor || objectB->GetObjectType() == GameObjectType::EnemyShip)
	{
		isDead = true;
		GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ship_Anim::Explode_Anim));
		leftSprtie.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
		rightSprite.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
	}
}