/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: EnemyShip.cpp
Project: CS230
Author: Hyunjun Lee
Creation date: 2022/6/8
-----------------------------------------------------------------*/
#include "EnemyShip.h"
#include "Ship_Anims.h"
#include "Flame_Anims.h"
#include "../Engine/ShowCollision.h"
#include "../Engine/Engine.h"
#include "../Engine/Collision.h"
#include "Score.h"

EnemyShip::EnemyShip(GameObject* player) : player(player), flameRight("Assets/flame.spt", this), flameLeft("Assets/flame.spt", this), isDead(false)
{
	AddGOComponent(new CS230::Sprite("Assets/enemyShip.spt", this));
	GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ship_Anim::None_Anim));
	SetRotation(((rand() % 1024) / 1024) * 2 * PI);
	SetPosition(player->GetPosition() + math::RotateMatrix(GetRotation()) * math::vec2{ 300, ((rand() % 1024) / 1024) * -250.0 });
	flameLeft.PlayAnimation(static_cast<int>(Flame_Anim::Flame_Anim));
	flameRight.PlayAnimation(static_cast<int>(Flame_Anim::Flame_Anim));
}

void EnemyShip::Update(double dt)
{
	flameLeft.Update(dt);
	flameRight.Update(dt);
	math::vec2 length = math::vec2({ player->GetPosition().x - GetPosition().x, player->GetPosition().y - GetPosition().y });
	if (length.Normalize().Cross(math::vec2({ math::RotateMatrix(GetRotation()) * math::vec2{ 0,1 } })) > 0.05)
	{
		UpdateRotation(-rotationRate * dt);
	}
	else if (length.Normalize().Cross(math::vec2({ math::RotateMatrix(GetRotation()) * math::vec2{ 0,1 } })) < -0.05)
	{
		UpdateRotation(rotationRate * dt);
	}
	UpdateVelocity(-(GetVelocity() * drag * dt));
	UpdatePosition({ GetVelocity() * dt });
	UpdateVelocity({ math::RotateMatrix(GetRotation()) * math::vec2{ 0,accel * dt } });
	UpdateGOComponents(dt);
}

void EnemyShip::Draw(math::TransformMatrix displayMatrix)
{
	GameObject::GetGOComponent<CS230::Sprite>()->Draw(GetMatrix() * displayMatrix);
	flameLeft.Draw(GetMatrix() * displayMatrix * math::TranslateMatrix(GetGOComponent<CS230::Sprite>()->GetHotSpot(1)));
	flameRight.Draw(GetMatrix() * displayMatrix * math::TranslateMatrix(GetGOComponent<CS230::Sprite>()->GetHotSpot(2)));
	ShowCollision* ShowCollision_ = Engine::GetGSComponent<ShowCollision>();
	CS230::Collision* Collision_ = GetGOComponent<CS230::Collision>();
	if (Collision_ != nullptr && ShowCollision_->IsEnabled() == true && ShowCollision_ != nullptr)
	{
		Collision_->Draw(displayMatrix);
	}
}

bool EnemyShip::CanCollideWith(GameObjectType collideAgainstType)
{
	if (collideAgainstType == GameObjectType::Ship)
	{
		return true;
	}
	if (collideAgainstType == GameObjectType::Laser)
	{
		return true;
	}
	return false;
}

void EnemyShip::ResolveCollision(GameObject* collidedWith)
{
	if (isDead == true)
	{
		SetVelocity({ 0, 0 });
		RemoveGOComponent<CS230::Collision>();
		flameLeft.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
		flameRight.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
		Engine::GetGSComponent<Score>()->AddScore(300);
	}
	if (collidedWith->GetObjectType() == GameObjectType::Ship)
	{
		flameLeft.PlayAnimation(static_cast<int>(Flame_Anim::Flame_Anim));
		flameRight.PlayAnimation(static_cast<int>(Flame_Anim::Flame_Anim));
	}
	if (collidedWith->GetObjectType() == GameObjectType::Laser)
	{
		isDead = true;
		GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ship_Anim::Explode_Anim));
		flameLeft.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
		flameRight.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
	}
}
