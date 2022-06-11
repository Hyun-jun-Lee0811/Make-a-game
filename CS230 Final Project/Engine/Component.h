/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Assignment: CS230 Final Project
File Name: Component.h
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022/5/9
-----------------------------------------------------------------*/
#pragma once

namespace CS230
{
	class Component
	{
	public:
		virtual ~Component() {};
		virtual void Update(double) {};
	};
}