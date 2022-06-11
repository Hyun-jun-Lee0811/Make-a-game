/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Assignment: CS230 Final Project
File Name: TreeStump.cpp
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022/4/30 spring
-----------------------------------------------------------------*/
#include "TreeStump.h"
#include "../Engine/Sprite.h"

TreeStump::TreeStump(math::vec2 pos, int size) : GameObject(pos)
{
	switch (size)
	{
	case 1:
		AddGOComponent(new CS230::Sprite("Assets/treeStump1.spt", this));
		break;
	case 2:
		AddGOComponent(new CS230::Sprite("Assets/treeStump2.spt", this));
		break;
	case 3:
		AddGOComponent(new CS230::Sprite("Assets/treeStump3.spt", this));
		break;
	case 5:
		AddGOComponent(new CS230::Sprite("Assets/treeStump5.spt", this));
		break;
	}
}