/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ShowCollision.h
Project: CS230
Author: Hyunjun Lee
Creation date: 2022/5/10
-----------------------------------------------------------------*/
#pragma once
#include "Input.h"
#include "Component.h"

class ShowCollision : public CS230::Component
{
public:
	ShowCollision(CS230::InputKey::Keyboard keyToUse);
	void Update(double) override;
	bool IsEnabled();
private:
	bool enabled;
	CS230::InputKey showCollisionKey;
};