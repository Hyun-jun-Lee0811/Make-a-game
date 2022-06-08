/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Score.cpp
Project: CS230
Author: Hyunjun Lee
Creation date: 2022/5/20
-----------------------------------------------------------------*/
#include "Score.h"
#include "Fonts.h"
#include "../Engine/Engine.h"

Score::Score(int startingScore, Fonts fontToUse) : fontToUse(fontToUse), score(startingScore)
{
	RenderText();
}

void Score::AddScore(int)
{
}

void Score::Draw(math::ivec2 location)
{
	scoreTexture.Draw(math::TranslateMatrix{ math::ivec2{location.x,location.y} });
}

void Score::RenderText()
{
	std::string scoreString = "Score: " + std::to_string(score / 100) + std::to_string((score % 100) / 10) + std::to_string(score % 10);
	if (fontToUse == Fonts::Font1)
	{
		scoreTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture(scoreString, 0xFFFFFFFF, true);
	}
	else
	{
		scoreTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font2)).DrawTextToTexture(scoreString, 0xFFFFFFFF, true);
	}
}