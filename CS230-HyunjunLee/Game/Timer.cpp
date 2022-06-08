/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Timer.cpp
Project: CS230
Author: Hyunjun Lee
Creation date: 2022/5/20
-----------------------------------------------------------------*/
#include "Timer.h"
#include "../Engine/Engine.h"
#include "Fonts.h"

Timer::Timer(int time) : timer(time) {}

void Timer::Update(double dt)
{
	timer -= dt;
	if (static_cast<int>(timer))
	{
		std::string timetexture = "Time: " + std::to_string(static_cast<int>(timer + 1));
		timeTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture(timetexture, 0xFFFFFFFF, true);
	}
}

void Timer::Draw(math::ivec2 location)
{
	timeTexture.Draw(math::TranslateMatrix{ math::ivec2{location.x,location.y} });
}

bool Timer::hasEnded()
{
	if (timer < 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}