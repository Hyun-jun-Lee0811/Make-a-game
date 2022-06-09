/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Cloud.h
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022/6/9
-----------------------------------------------------------------*/
#include "Cloud.h"

Cloud::Cloud(math::vec2 pos, int size) : GameObject(pos)
{
	switch (size)
	{
	case 1:
		AddGOComponent(new CS230::Sprite("Assets/Cloud1.spt", this));
		break;
	case 2:
		AddGOComponent(new CS230::Sprite("Assets/Cloud2.spt", this));
		break;
	case 3:
		AddGOComponent(new CS230::Sprite("Assets/Cloud3.spt", this));
		break;
	case 5:
		AddGOComponent(new CS230::Sprite("Assets/Cloud4.spt", this));
		break;
	}
}
