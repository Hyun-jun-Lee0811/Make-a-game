/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Assignment: CS230 Final Project
File Name: GameStateManager.cpp
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022 4/16 spring
-----------------------------------------------------------------*/
#include "GameState.h"
#include "GameStateManager.h"
#include "Engine.h"
#include "GameObjectManager.h"

CS230::GameStateManager::GameStateManager() : currGameState(nullptr), nextGameState(nullptr)
{
	state = CS230::GameStateManager::State::START;
}

void CS230::GameStateManager::AddGameState(GameState& gameState)
{
	gameStates.push_back(&gameState);
}

void CS230::GameStateManager::SetNextState(int initState)
{
	nextGameState = gameStates[initState];
}

void CS230::GameStateManager::Shutdown()
{
	nextGameState = nullptr;
}

void CS230::GameStateManager::ReloadState()
{
	state = CS230::GameStateManager::State::UNLOAD;
}

void CS230::GameStateManager::Update(double dt)
{
	switch (state)
	{
	case CS230::GameStateManager::State::START:
		if (gameStates.empty() == true)
		{
			Engine::GetLogger().LogError("Error no state");
			state = CS230::GameStateManager::State::SHUTDOWN;
		}
		else
		{
			nextGameState = gameStates[0];
			state = CS230::GameStateManager::State::LOAD;
		}
		break;

	case CS230::GameStateManager::State::LOAD:
		currGameState = nextGameState;
		Engine::GetLogger().LogEvent("Load " + currGameState->GetName());
		currGameState->Load();
		Engine::GetLogger().LogEvent("Load complete");
		state = CS230::GameStateManager::State::UPDATE;
		break;

	case CS230::GameStateManager::State::UPDATE:
		if (currGameState != nextGameState) 
		{
			state = CS230::GameStateManager::State::UNLOAD;
		}
		else
		{
			Engine::GetLogger().LogVerbose("Update " + currGameState->GetName());
			currGameState->Update(dt);
			if (GetGSComponent<GameObjectManager>() != nullptr)
			{
				GetGSComponent<GameObjectManager>()->CollideTest();
			}
			currGameState->Draw();
		}
		break;

	case CS230::GameStateManager::State::UNLOAD:
		Engine::GetLogger().LogEvent("Unload " + currGameState->GetName());

		currGameState->Unload();
		if (currGameState != nextGameState)
		{
			Engine::GetTextureManager().Unload();
			Engine::GetLogger().LogEvent("Clear Texture");
		}
		if (nextGameState == nullptr)
		{
			state = CS230::GameStateManager::State::SHUTDOWN;
		}
		else
		{
			state = CS230::GameStateManager::State::LOAD;
		}

		break;

	case CS230::GameStateManager::State::SHUTDOWN:
		state = CS230::GameStateManager::State::EXIT;
		break;

	case CS230::GameStateManager::State::EXIT:
		break;
	}
}