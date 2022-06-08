/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: MainMenu.cpp
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022/5/2 Spring
-----------------------------------------------------------------*/
#include "MainMenu.h"
#include "../Engine/Engine.h"
#include "Fonts.h"
#include "Screens.h"

MainMenu::MainMenu() : upKey(CS230::InputKey::Keyboard::Up), downKey(CS230::InputKey::Keyboard::Down),
selectKey(CS230::InputKey::Keyboard::Enter), selectedIndex(static_cast<int>(Options::Mode1)) {}

MainMenu::OptionData MainMenu::optionsData[static_cast<int>(MainMenu::Options::Count)] =
{
	{"Side Scroller", {0.5, 0.45}, {} },
	{"Space Shooter", {0.5, 0.35}, {} },
	{"Watch Your Step", {0.5, 0.25}, {} },
	{"Quit", {0.5, 0.15}, {} },
};

void MainMenu::Load()
{
	title = Engine::GetSpriteFont(static_cast<int>(Fonts::Font2)).DrawTextToTexture("CS230 Project", 0xFFFFFFFF, true);
	for (OptionData& data : optionsData)
	{
		RenderOption(data, false);
	}
	selectedIndex = static_cast<int>(Options::Mode1);
	RenderOption(optionsData[selectedIndex], true);
}

void MainMenu::Update(double)
{
	if (upKey.IsKeyReleased() == true)
	{
		RenderOption(optionsData[selectedIndex], false);
		if (selectedIndex != 0)
		{
			selectedIndex--;
		}
		RenderOption(optionsData[selectedIndex], true);
	}
	if (downKey.IsKeyReleased() == true)
	{
		RenderOption(optionsData[selectedIndex], false);
		if (selectedIndex != static_cast<int>(Options::Count) - 1)
		{
			selectedIndex++;
		}
		RenderOption(optionsData[selectedIndex], true);
	}
	if (selectKey.IsKeyReleased() == true)
	{
		switch (static_cast<Options>(selectedIndex))
		{
		case Options::Mode1:
			Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Mode1));
			break;
		case Options::Mode2:
			Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Mode2));
			break;
		case Options::Mode3:
			Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Mode3));
			break;
		case Options::Quit:
			Engine::GetGameStateManager().Shutdown();
			break;
		}
	}
}

void MainMenu::Unload() {}

void MainMenu::Draw()
{
	Engine::GetWindow().Clear(0x87ceeb);
	math::ivec2 windowSize = Engine::GetWindow().GetSize();
	title.Draw(math::TranslateMatrix(math::ivec2{ windowSize.x / 2 - title.GetSize().x, windowSize.y / 2 + 110 }) * math::ScaleMatrix({ 2,2 }));
	for (OptionData& option : optionsData)
	{
		math::ivec2 position = { static_cast<int>(windowSize.x * option.positionPercent.x), static_cast<int>(windowSize.y * option.positionPercent.y) };
		option.texture.Draw(math::TranslateMatrix{ position - option.texture.GetSize() / 2 });
	}
}

void MainMenu::RenderOption(OptionData& data, bool isHighlighted)
{
	data.texture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture
	(data.text, (isHighlighted == true) ? MainMenu::onColor : MainMenu::offColor, true);
}