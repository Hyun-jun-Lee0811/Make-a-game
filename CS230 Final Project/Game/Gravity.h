/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Assignment: CS230 Final Project
File Name: Gravity.h
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022/5/10
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\Component.h" 

class Gravity : public CS230::Component
{
public:
	Gravity(double value) : gravity(value) {}
	double GetValue() { return gravity; }
private:
	double gravity;
};