/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: main.cpp
Project: CS230
Author: Hyunjun Lee
Creation date: 2022/4/16 Spring
-----------------------------------------------------------------*/
#include <stdexcept>
#include <iostream>

#include "Game/MainMenu.h"
#include "Engine/Engine.h"
#include "Game/Splash.h"
#include "Game/Mode1.h"
#include "Game/Mode2.h"
#include "Game/Screens.h"

int main(void)
{
	try
	{
		Engine& engine = Engine::Instance();
		engine.Init("Week 12 - Hyunjun Lee");
		engine.AddSpriteFont("Assets/font.png");
		engine.AddSpriteFont("Assets/font2.png");
		Splash splash;
		MainMenu main_menu;
		Mode1 mode1;
		Mode2 mode2;
		engine.GetGameStateManager().AddGameState(splash);
		engine.GetGameStateManager().AddGameState(main_menu);
		engine.GetGameStateManager().AddGameState(mode1);
		engine.GetGameStateManager().AddGameState(mode2);

		while (engine.HasGameEnded() == false)
		{
			engine.Update();
		}
		engine.Shutdown();
		return 0;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << "\n";
		return -1;
	}
}