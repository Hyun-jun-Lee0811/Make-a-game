/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: MainMenu.h
Project: CS230
Author: Hyunjun Lee
Creation date: 2022/5/2 Spring
-----------------------------------------------------------------*/
#pragma once
#include <string>
#include "..\Engine\GameState.h"
#include  "../Engine/Vec.h"
#include "..\Engine\Input.h"
#include "..\Engine\Texture.h"

class MainMenu : public CS230::GameState
{
public:
	enum class Options
	{
		Mode1,
		Mode2,
		Quit,
		Count,
	};

	MainMenu();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;

	std::string GetName() override { return "MainMenu"; }
private:
	struct OptionData
	{
		std::string text;
		math::vec2 positionPercent;
		CS230::Texture texture;
	};

	void RenderOption(OptionData& data, bool isHighlighted);

	CS230::Texture title;
	static OptionData optionsData[static_cast<int>(MainMenu::Options::Count)];
	int selectedIndex;

	CS230::InputKey upKey;
	CS230::InputKey downKey;
	CS230::InputKey selectKey;

	static const unsigned int offColor = 0x404040FF;
	static const unsigned int onColor = 0xFFFFFFFF;

	//int cs230_project;
	//int side_scroller;
	//int space_shooter;
	//int quit;
	//CS230::Texture Side_Scroller_texture;
	//CS230::Texture Space_Shooter_texture;
	//CS230::Texture Quit_texture;
};