/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Assignment: CS230 Final Project
File Name: Bunny.cpp
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022/4/16 spring
-----------------------------------------------------------------*/
#include "Bunny.h"
#include "../Engine/Collision.h"
#include "Bunny_Anim.h"
#include "../Engine/Engine.h"
#include "Score.h"
#include "../Engine/Sprite.h"

Bunny::Bunny(math::vec2 pos, std::vector<double> patrolNodes, Hero* heroPtr) : GameObject(pos), patrolNodes(patrolNodes), heroPtr(heroPtr), currPatrolNode(0)
{
	AddGOComponent(new CS230::Sprite("Assets/Bunny.spt", this));
	GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Bunny_Anim::Walk_Anim));
	currState = &statePatrol;
	currState->Enter(this);
}

void Bunny::ResolveCollision(GameObject* objectA)
{
	if (objectA->GetObjectType() == GameObjectType::Hero)
	{
		Engine::GetGSComponent<Score>()->AddScore(100);
		ChangeState(&stateDead);
	}
}

void Bunny::State_Attack::Enter(GameObject* object)
{
	Bunny* Bunny_ = static_cast<Bunny*>(object);
	Bunny_->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Bunny_Anim::Attack_Anim));

	if (Bunny_->GetPosition().x > Bunny_->patrolNodes[Bunny_->currPatrolNode])
	{
		Bunny_->SetVelocity(math::vec2{ -velocity * 2 ,0 });
		Bunny_->SetScale({ -1, 1 });
	}
	else
	{
		Bunny_->SetVelocity(math::vec2{ velocity * 2 ,0 });
		Bunny_->SetScale({ 1, 1 });
	}
}

void Bunny::State_Attack::Update(GameObject* object, double)
{
	Bunny* bunny_ = static_cast<Bunny*>(object);

	if (bunny_->GetPosition().x >= bunny_->patrolNodes[bunny_->currPatrolNode] && bunny_->GetVelocity().x >= 0
		|| bunny_->GetPosition().x <= bunny_->patrolNodes[bunny_->currPatrolNode] && bunny_->GetVelocity().x <= 0)
	{
		if (bunny_->currPatrolNode == bunny_->patrolNodes.size() - 1)
		{
			bunny_->currPatrolNode = 0;
		}
		else
		{
			bunny_->currPatrolNode++;
		}
		bunny_->ChangeState(&bunny_->statePatrol);
	}
}

void Bunny::State_Attack::TestForExit(GameObject*) {}

void Bunny::State_Dead::Enter(GameObject* object)
{
	Bunny* bunny_ = static_cast<Bunny*>(object);
	bunny_->RemoveGOComponent<CS230::Collision>();
	bunny_->SetVelocity(math::vec2{ 0, 0 });
	bunny_->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Bunny_Anim::Dead_Anim));
	Engine::GetGSComponent<Score>()->AddScore(100);
}

void Bunny::State_Dead::Update(GameObject*, double) {}

void Bunny::State_Dead::TestForExit(GameObject*) {}

void Bunny::State_Patrol::Enter(GameObject* object)
{
	Bunny* bunny_ = static_cast<Bunny*>(object);
	bunny_->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Bunny_Anim::Walk_Anim));
	if (bunny_->GetPosition().x > bunny_->patrolNodes[bunny_->currPatrolNode])
	{
		bunny_->SetScale(math::vec2{ -1.0, 1.0 });
		bunny_->SetVelocity(math::vec2{ -velocity, 0 });
	}
	if (bunny_->GetPosition().x < bunny_->patrolNodes[bunny_->currPatrolNode])
	{
		bunny_->SetScale(math::vec2{ 1.0, 1.0 });
		bunny_->SetVelocity(math::vec2{ velocity, 0 });
	}
}

void Bunny::State_Patrol::Update(GameObject* object, double)
{
	Bunny* bunny_ = static_cast<Bunny*>(object);
	if (bunny_->GetPosition().x >= bunny_->patrolNodes[bunny_->currPatrolNode] && bunny_->GetVelocity().x >= 0 || bunny_->GetPosition().x <= bunny_->patrolNodes[bunny_->currPatrolNode] && bunny_->GetVelocity().x <= 0)
	{
		if (bunny_->currPatrolNode == bunny_->patrolNodes.size() - 1)
		{
			bunny_->currPatrolNode = 0;
		}
		else
		{
			bunny_->currPatrolNode++;
		}
		bunny_->ChangeState(this);
	}
}

void Bunny::State_Patrol::TestForExit(GameObject* object)
{
	Bunny* bunny_ = static_cast<Bunny*>(object);
	if (bunny_->GetPosition().y == bunny_->heroPtr->GetPosition().y)
	{
		if ((bunny_->heroPtr->GetPosition().x > bunny_->GetPosition().x && bunny_->GetVelocity().x > 0) || (bunny_->heroPtr->GetPosition().x < bunny_->GetPosition().x && bunny_->GetVelocity().x < 0))
		{
			if ((bunny_->heroPtr->GetPosition().x < bunny_->patrolNodes[bunny_->currPatrolNode] && bunny_->heroPtr->GetPosition().x > bunny_->GetPosition().x) || (bunny_->heroPtr->GetPosition().x > bunny_->patrolNodes[bunny_->currPatrolNode] && bunny_->heroPtr->GetPosition().x < bunny_->GetPosition().x))
			{
				bunny_->ChangeState(&bunny_->stateAttack);
			}
		}
	}
}
