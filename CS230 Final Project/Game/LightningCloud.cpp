/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: LightningCloud.cpp
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022/6/11
-----------------------------------------------------------------*/
#include "LightningCloud.h"

LightningCloud::LightningCloud(math::vec2 startPos) : GameObject(startPos)
{
	AddGOComponent(new CS230::Sprite("Assets/LightningCloud.spt", this));
}