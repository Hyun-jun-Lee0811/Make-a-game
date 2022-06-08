/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Meteor.cpp
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022/4/30 spring
-----------------------------------------------------------------*/
#include "Meteor.h"
#include "ScreenWrap.h"
#include "..\Engine\GameObject.h"
#include "..\Engine\Engine.h"
#include "Meteor_Anims.h"
#include "..\Engine\GameObjectManager.h"
#include "..\Engine\Collision.h"
#include "Score.h"
#include "../Engine/ParticleEmitter.h"
#include "GameParticles.h"

const double PI = 3.14;


Meteor::Meteor() : GameObject({ 0,0 }), health(100), size(1)
{
	AddGOComponent(new CS230::Sprite("Assets/Meteor.spt", this));
	AddGOComponent(new ScreenWrap(*this));
	SetPosition({ rand() });
	//SetRotation({ rand() % 10 +  PI});
	SetVelocity({ rand() % 200 - 100 });
	SetScale({ rand() % 3 - 0.35 });
}

Meteor::Meteor(Meteor& original) : GameObject(original.GetPosition()), size(original.size), health(100)
{
	AddGOComponent(new CS230::Sprite("Assets/Meteor.spt", this));
	AddGOComponent(new ScreenWrap(*this));
	GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Meteor_Anim::None_Anim));
	size = original.size + 1;
	double Meteor = 0;
	switch (size)
	{
	case 2:
		Meteor = (rand() % 1020) / 4054.0 + .48;
		break;
	case 3:
		Meteor = (rand() % 1020) / 4054.0 + .23;
		break;
	}
	SetScale({ Meteor });
}

void Meteor::Update(double dt)
{
	GameObject::Update(dt);
	GetGOComponent < ScreenWrap >()->Update(dt);
	if ((static_cast<Meteor_Anim>(GetGOComponent<CS230::Sprite>()->GetCurrentAnim())
		== Meteor_Anim::Fade_Anim)
		&& GetGOComponent<CS230::Sprite>()->IsAnimationDone() == true)
	{
		destroy();
	}
}

void Meteor::ResolveCollision(GameObject* objectB)
{
	if (objectB->GetObjectType() == GameObjectType::Laser)
	{
		health -= 10;
		math::vec2 location = objectB->GetPosition() - GetPosition();
		Engine::GetGSComponent<HitEmitter>()->Emit(1, location.Normalize() * GetGOComponent<CS230::CircleCollision>()->GetRadius() + GetPosition(), GetVelocity(), { 0, 0 }, 0);
		Engine::GetGSComponent<MeteorBitEmitter>()->Emit(10, location.Normalize() * GetGOComponent<CS230::CircleCollision>()->GetRadius() + GetPosition(), GetVelocity(), (location.Normalize() * 2.0 + objectB->GetVelocity().Normalize()) * 100.0, PI / 2.0);
	};

	if (health <= 0)
	{
		if (size <= 3)
		{
			Meteor* METEOR = new Meteor(*this);
			Meteor* METEORS = new Meteor(*this);
			METEOR->SetVelocity(math::RotateMatrix(PI / 6) * objectB->GetVelocity());
			METEORS->SetVelocity(math::RotateMatrix(-PI / 6) * objectB->GetVelocity());
			Engine::GetGSComponent<CS230::GameObjectManager>()->Add(METEOR);
			Engine::GetGSComponent<CS230::GameObjectManager>()->Add(METEORS);
		}
		GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Meteor_Anim::Fade_Anim));
		Engine::GetGSComponent<Score>()->AddScore(100 * size);
		GameObject::RemoveGOComponent<CS230::Collision>();
	}
	else
	{
		UpdateVelocity(math::vec2{ 0.01 * objectB->GetVelocity() });
	}
}