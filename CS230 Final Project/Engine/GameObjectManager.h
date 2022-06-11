/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Assignment: CS230 Final Project
File Name: GameObjectManager.h
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022/4/30 spring
-----------------------------------------------------------------*/
#pragma once
#include <vector>
#include <list>
#include "GameObject.h"
#include "../Game/Hero.h"
#include "../Game/Ball.h"
#include "../Game/Ship.h"

namespace math { class TransformMatrix; }

namespace CS230
{
	class GameObject;

	class GameObjectManager : public Component
	{
	public:
		void Add(GameObject* obj);
		~GameObjectManager();
		void Update(double dt) override;
		void DrawAll(math::TransformMatrix& cameraMatrix);
		void CollideTest();
		const std::list<GameObject*>& Objects() { return gameObjects; }
	private:
		std::list<GameObject*> gameObjects;
		std::vector<GameObject*> store;
	};
}