/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Win.h
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022/6/11
-----------------------------------------------------------------*/
#pragma once
#include <string>
#include "..\Engine\GameState.h"
#include  "../Engine/Vec.h"
#include "..\Engine\Input.h"
#include "..\Engine\Texture.h"
#include "Mode3.h"

class Win : public CS230::GameState
{
public:
	enum class Options
	{
		Main_Menu,
		Mode1,
		Mode2,
		Quit,
		Count,
	};

	Win();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;

	std::string GetName() override { return "Win"; }
private:
	struct OptionData
	{
		std::string text;
		math::vec2 positionPercent;
		CS230::Texture texture;
	};

	void RenderOption(OptionData& data, bool isHighlighted);

	CS230::Texture title;
	static OptionData optionsData[static_cast<int>(Win::Options::Count)];
	int selectedIndex;

	CS230::InputKey upKey;
	CS230::InputKey downKey;
	CS230::InputKey selectKey;
	CS230::GameObjectManager* gameObjectManager;
	Background* back;

	static const unsigned int offColor = 0x404040FF;
	static const unsigned int onColor = 0xFFFFFFFF;
};