/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ScreenWrap.cpp
Project: CS230
Author: Hyunjun Lee
Creation date: 2022/5/10
-----------------------------------------------------------------*/
#include "ScreenWrap.h"
#include "..\Engine\Engine.h"

void ScreenWrap::Update(double)
{
	const math::vec2 WindowSize = math::vec2{ Engine::GetWindow().GetSize() };
	const math::vec2 ScreenSize = math::vec2{ object.GetGOComponent<CS230::Sprite>()->GetFrameSize() / 2 };

	if (object.GetPosition().x + ScreenSize.x < 0)
	{
		object.SetPosition({ WindowSize.x + ScreenSize.x , object.GetPosition().y });
	}
	else if (object.GetPosition().x - ScreenSize.x > WindowSize.x)
	{
		object.SetPosition({ -ScreenSize.x , object.GetPosition().y });

	}
	else if (object.GetPosition().y - ScreenSize.y > WindowSize.y)
	{
		object.SetPosition({ object.GetPosition().x , -ScreenSize.y });
	}
	else if (object.GetPosition().y + ScreenSize.y < 0)
	{
		object.SetPosition({ object.GetPosition().x ,WindowSize.y + ScreenSize.y });
	}
}