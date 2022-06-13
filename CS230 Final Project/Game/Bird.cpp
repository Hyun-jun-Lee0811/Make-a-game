/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Assignment: CS230 Final Project
File Name: Bird.cpp
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022/6/9
-----------------------------------------------------------------*/
#include "Bird.h"
#include "Bird_Anim.h"
#include "../Engine/Collision.h"
#include "../Engine/Engine.h"
#include "Score.h"
#include "../Engine/Sprite.h"

Bird::Bird(math::vec2 pos, std::vector<double> patrolNodes, Player* playerPtr) : GameObject(pos), patrolNodes(patrolNodes), playerPtr(playerPtr), currPatrolNode(0)
{
	AddGOComponent(new CS230::Sprite("Assets/Bird.spt", this));
	GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Bird_Anim::Fly_Anim));
	currState = &statePatrol;
	currState->Enter(this);
}



void Bird::Fly::Enter(GameObject* object)
{
	Bird* bird = static_cast<Bird*>(object);
	bird->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Bird_Anim::Fly_Anim));
	if (bird->GetPosition().x > bird->patrolNodes[bird->currPatrolNode])
	{
		bird->SetScale(math::vec2{ -1.0, 1.0 });
		bird->SetVelocity(math::vec2{ -velocity, 0 });
	}
	if (bird->GetPosition().x < bird->patrolNodes[bird->currPatrolNode])
	{
		bird->SetScale(math::vec2{ 1.0, 1.0 });
		bird->SetVelocity(math::vec2{ velocity, 0 });
	}
}

void Bird::Fly::Update(GameObject* object, double)
{
	Bird* bird = static_cast<Bird*>(object);
	if (bird->GetPosition().x >= bird->patrolNodes[bird->currPatrolNode] && bird->GetVelocity().x >= 0 || bird->GetPosition().x <= bird->patrolNodes[bird->currPatrolNode] && bird->GetVelocity().x <= 0)
	{
		if (bird->currPatrolNode == bird->patrolNodes.size() - 1)
		{
			bird->currPatrolNode = 0;
		}
		else
		{
			bird->currPatrolNode++;
		}
		bird->ChangeState(this);
	}
}

void Bird::Fly::TestForExit(GameObject* object)
{
	Bird* bird = static_cast<Bird*>(object);
	if (bird->GetPosition().y == bird->playerPtr->GetPosition().y)
	{
		if ((bird->playerPtr->GetPosition().x > bird->GetPosition().x && bird->GetVelocity().x > 0) || (bird->playerPtr->GetPosition().x < bird->GetPosition().x && bird->GetVelocity().x < 0))
		{
			if ((bird->playerPtr->GetPosition().x < bird->patrolNodes[bird->currPatrolNode] && bird->playerPtr->GetPosition().x > bird->GetPosition().x) || (bird->playerPtr->GetPosition().x > bird->patrolNodes[bird->currPatrolNode] && bird->playerPtr->GetPosition().x < bird->GetPosition().x))
			{
				bird->ChangeState(&bird->statePatrol);
			}
		}
	}
}