/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Assignment: CS230 Final Project
File Name: GameObjectManager.cpp
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022/4/30 spring
-----------------------------------------------------------------*/
#include "GameObjectManager.h"
#include "Engine.h"

void CS230::GameObjectManager::Add(GameObject* obj)
{
	gameObjects.push_back(obj);
}

CS230::GameObjectManager::~GameObjectManager()
{
	for (GameObject* unload : gameObjects)
	{
		delete unload;
	}
	gameObjects.clear();
}

void CS230::GameObjectManager::Update(double dt)
{
	for (GameObject* update_All : gameObjects)
	{
		if (update_All != nullptr)
		{
			update_All->Update(dt);
		}
		if (update_All->GameObject::destroy_check() == true)
		{
			store.push_back(update_All);
		}
	}
	for (GameObject* STORE : store)
	{
		gameObjects.remove(STORE);
		if (STORE == nullptr)
		{
			delete STORE;
		}
	}
}

void CS230::GameObjectManager::DrawAll(math::TransformMatrix& cameraMatrix)
{
	for (GameObject* darw_All : gameObjects)
	{
		if (darw_All != nullptr)
		{
			darw_All->Draw(cameraMatrix);
		}
	}
}

void CS230::GameObjectManager::CollideTest()
{
	for (GameObject* gameobjectA : gameObjects)
	{
		if (gameobjectA != nullptr)
		{
			for (GameObject* gameobjectB : gameObjects)
			{
				if (gameobjectB != nullptr)
				{
					if (gameobjectA->CanCollideWith(gameobjectB->GetObjectType()) && gameobjectA != gameobjectB)
					{
						if (gameobjectA->DoesCollideWith(gameobjectB))
						{
							if (gameobjectA->GetObjectTypeName() != gameobjectB->GetObjectTypeName())
								Engine::GetLogger().LogEvent("Collision Detected: " + gameobjectA->GetObjectTypeName() + " And " + gameobjectB->GetObjectTypeName());
							gameobjectA->ResolveCollision(gameobjectB);
						}
					}
				}
			}
		}
	}
}