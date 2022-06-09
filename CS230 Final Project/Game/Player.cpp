/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Player.h
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022/6/9
-----------------------------------------------------------------*/
#include "Player.h"
#include "../Engine/Engine.h"
#include "Gravity.h"
#include "Player_Anims.h"
#include "../Engine/Collision.h"
#include "../Engine/Camera.h"

Player::Player(math::vec2 startPos) : GameObject(startPos), jumpKey(CS230::InputKey::Keyboard::Up),
moveLeftKey(CS230::InputKey::Keyboard::Left), moveRightKey(CS230::InputKey::Keyboard::Right), isDead(false), drawPlayer(true), Playertimer(0)
{
	AddGOComponent(new CS230::Sprite("Assets/Hero.spt", this));
	currState = &stateIdle;
	currState->Enter(this);
	standingOnObject = this;
}

void Player::Update(double dt)
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

	if (Playertimer != 0)
	{
		drawPlayer = !drawPlayer;
		Playertimer -= dt;
		if (Playertimer < 0)
		{
			drawPlayer = true;
			Playertimer = 0;
		}
	}
	//if (moveLeftKey.IsKeyDown() == true || moveRightKey.IsKeyDown() == true)
	//{
	//	Player* player = static_cast<Player*>(objectD);
	//	player->ChangeState(&player->stateFalling);
	//}
}

void Player::Draw(math::TransformMatrix displayMatrix)
{
	if (drawPlayer == true)
	{
		GameObject::Draw(displayMatrix);
	}
}

math::vec2 Player::GetPosition()
{
	return GameObject::GetPosition();
}

bool Player::CanCollideWith(GameObjectType gameobjecttypeB)
{
	if (gameobjecttypeB == GameObjectType::Particle)
	{
		return false;
	}
	return true;
}

void Player::ResolveCollision(GameObject* objectB)
{
	math::rect2 collideRect = objectB->GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect();
	math::rect2 playerRect = GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect();

	switch (objectB->GetObjectType())
	{
	case GameObjectType::Cloud:
		if (currState == &stateFalling)
		{
			if (playerRect.Top() > collideRect.Top() && objectB->DoesCollideWith(GetPosition()))
			{
				SetPosition({ GetPosition().x, collideRect.Top() });
				standingOnObject = objectB;
				currState->TestForExit(this);
				return;
			}
		}
		if (currState == &stateJumping)
		{
			if (playerRect.Top() < collideRect.Bottom() && objectB->DoesCollideWith(GetPosition()))
			{
				SetPosition({  collideRect.Bottom() });
				//standingOnObject = objectB;
				currState->TestForExit(this);
				return;
			}
		}
		if (GetPosition().x > objectB->GetPosition().x)
		{
			SetPosition(math::vec2{ collideRect.Right() + playerRect.Size().x / 2,GetPosition().y });
			SetVelocity(math::vec2{ 0,GetVelocity().y });
		}
		if (GetPosition().x < objectB->GetPosition().x)
		{
			SetPosition(math::vec2{ collideRect.Left() - playerRect.Size().x / 2,GetPosition().y });
			SetVelocity(math::vec2{ 0,GetVelocity().y });
		}
		break;
	}
}

void Player::UpdateXVelocity(double dt)
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

void Player::State_Idle::Enter(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	player->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Player_Anims::Player_Idle_Anim));
	if (player->standingOnObject == nullptr)
	{
		Engine::GetLogger().LogError("State_Idle Error!!");
	}
}

void Player::State_Idle::Update(GameObject*, double) {}

void Player::State_Idle::TestForExit(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	if (player->moveLeftKey.IsKeyDown() == true)
	{
		player->ChangeState(&player->stateRunning);
	}
	if (player->moveRightKey.IsKeyDown() == true)
	{
		player->ChangeState(&player->stateRunning);
	}
	if (player->jumpKey.IsKeyDown() == true)
	{
		player->ChangeState(&player->stateJumping);
	}
}

void Player::State_Running::Enter(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	player->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Player_Anims::Player_Run_Anim));

	if (player->standingOnObject == nullptr)
	{
		Engine::GetLogger().LogError("State_Running Error!!");
	}
	if (player->moveLeftKey.IsKeyDown() == true)
	{
		player->SetScale({ math::vec2{-1.0,1.0} });
	}
	if (player->moveRightKey.IsKeyDown() == true)
	{
		player->SetScale({ math::vec2{1.0,1.0} });
	}
}

void Player::State_Running::Update(GameObject* object, double dt)
{
	Player* player = static_cast<Player*>(object);
	player->UpdateXVelocity(dt);
}

void Player::State_Running::TestForExit(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	if (player->moveLeftKey.IsKeyDown() == true && player->GetVelocity().x > 0)
	{
		player->ChangeState(&player->stateSkidding);
	}
	if (player->moveRightKey.IsKeyDown() == true && player->GetVelocity().x < 0)
	{
		player->ChangeState(&player->stateSkidding);
	}
	if (player->GetVelocity().x == 0)
	{
		player->ChangeState(&player->stateIdle);
	}
	if (player->jumpKey.IsKeyDown() == true)
	{
		player->ChangeState(&player->stateJumping);
	}
	if (player->standingOnObject != nullptr && player->standingOnObject->DoesCollideWith(player->GetPosition()) == false)
	{
		player->standingOnObject = nullptr;
		player->ChangeState(&player->stateFalling);
	}
}

void Player::State_Skidding::Enter(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	player->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Player_Anims::Player_Fall_Anim));
}

void Player::State_Skidding::Update(GameObject* object, double dt)
{
	Player* player = static_cast<Player*>(object);
	player->UpdateXVelocity(dt);
}

void Player::State_Skidding::TestForExit(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	if (player->jumpKey.IsKeyDown() == true)
	{
		player->ChangeState(&player->stateJumping);
	}

	if (player->moveLeftKey.IsKeyDown() == true)
	{
		if (player->GameObject::GetVelocity().x <= 0)
		{
			player->ChangeState(&player->stateRunning);
		}
	}
	else if (player->moveRightKey.IsKeyDown() == true)
	{
		if (player->GameObject::GetVelocity().x >= 0)
		{
			player->ChangeState(&player->stateRunning);
		}
	}
	else if (player->moveLeftKey.IsKeyDown() == false && player->moveRightKey.IsKeyDown() == false)
	{
		player->ChangeState(&player->stateRunning);
	}
}

void Player::State_Jumping::Enter(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	player->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Player_Anims::Player_Jump_Anim));
	player->GameObject::SetVelocity({ player->GameObject::GetVelocity().x , Player::jumpVelocity });
	player->standingOnObject = nullptr;
}

void Player::State_Jumping::Update(GameObject* object, double dt)
{
	Player* player = static_cast<Player*>(object);
	player->UpdateVelocity({ 0, -Engine::GetGSComponent<Gravity>()->GetValue() * dt });
	player->UpdateXVelocity(dt);
}

void Player::State_Jumping::TestForExit(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	if (player->jumpKey.IsKeyDown() == false)
	{
		player->ChangeState(&player->stateFalling);
		player->GameObject::SetVelocity({ player->GameObject::GetVelocity().x , 0 });
	}
	else if (player->GameObject::GetVelocity().y <= 0)
	{
		player->ChangeState(&player->stateFalling);
	}
}

void Player::State_Falling::Enter(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	player->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Player_Anims::Player_Fall_Anim));
}

void Player::State_Falling::Update(GameObject* object, double dt)
{
	Player* player = static_cast<Player*>(object);
	player->GameObject::UpdateVelocity({ 0,-Engine::GetGSComponent<Gravity>()->GetValue() * dt });
	player->UpdateXVelocity(dt);
}

void Player::State_Falling::TestForExit(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	if (player->standingOnObject != nullptr)
	{
		if (player->GameObject::GetVelocity().x > 0)
		{
			if (player->moveLeftKey.IsKeyDown() == true)
			{
				player->ChangeState(&player->stateSkidding);
			}
			else
			{
				player->ChangeState(&player->stateRunning);
			}
		}
		else if (player->GameObject::GetVelocity().x <= 0)
		{
			if (player->moveRightKey.IsKeyDown() == true)
			{
				player->ChangeState(&player->stateSkidding);
			}
			else
			{
				player->ChangeState(&player->stateRunning);
			}
		}
		else
		{
			player->ChangeState(&player->stateIdle);
		}
		player->GameObject::SetVelocity({ player->GameObject::GetVelocity().x , 0 });
	}
	if (player->GetPosition().y < -280)
	{
		player->isDead = true;
	}
}