/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ShowCollision.cpp
Project: CS230
Author: Hyunjun Lee
Creation date: 2022/5/10
-----------------------------------------------------------------*/
#include "ShowCollision.h"

ShowCollision::ShowCollision(CS230::InputKey::Keyboard keyToUse) : showCollisionKey(keyToUse), enabled(false) {}

void ShowCollision::Update(double)
{
	if (showCollisionKey.IsKeyReleased() == true)
	{
		enabled = true;
		if (showCollisionKey.IsKeyDown() == true) { enabled = false; }
	}
}

bool ShowCollision::IsEnabled()
{
	return enabled;
}
