/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Engine.cpp
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022 4/16 spring
-----------------------------------------------------------------*/
#include "Engine.h"
#include "GameStateManager.h"

Engine::Engine() : frameCount(0), lastTick(std::chrono::system_clock::now()),
#ifdef _DEBUG				
logger(CS230::Logger::Severity::Debug, true, lastTick)
#else 						
logger(CS230::Logger::Severity::Event, false, lastTick)
#endif
{}
Engine::~Engine() {}

void Engine::Init(std::string windowName)
{
	fpsCalcTime = lastTick;
	window.Init(windowName);
	logger.LogEvent("Engine Init");

	int seed = static_cast<unsigned int>(time(NULL));
	srand(seed);
}

void Engine::Shutdown()
{
	logger.LogEvent("Engine Shutdown");
}

void Engine::Update()
{
	std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
	double dt = std::chrono::duration<double>(now - lastTick).count();
	if (dt >= 1.0 / Target_FPS)
	{
		GetLogger().LogVerbose("Engine Update");
		gameStateManager.Update(dt);
		lastTick = now;
		input.Update();
		window.Update();
		++frameCount;
		if (frameCount > FPS_IntervalFrameCount)
		{
			double averageFrameRate = frameCount / std::chrono::duration<double>(now - fpsCalcTime).count();
			GetLogger().LogEvent("FPS:  " + std::to_string(averageFrameRate));
			frameCount = 0;
			fpsCalcTime = now;
		}
	}
}

bool Engine::HasGameEnded()
{
	return gameStateManager.HasGameEnded();
}

void Engine::AddSpriteFont(const std::filesystem::path& fileName)
{
	fonts.push_back(fileName);
}