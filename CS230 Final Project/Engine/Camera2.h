/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Assignment: CS230 Final Project
File Name: Camera2.h
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022 6/13 spring
-----------------------------------------------------------------*/
#pragma once
#include "Vec.h"
#include "Rect.h"
#include "../Game/Player.h"

namespace CS230
{
	class Camera2 : public Component
	{
	public:
		Camera2(math::rect2 movableRange);
		void SetPosition(math::vec2 newPosition);
		const math::vec2& GetPosition() const;
		void SetExtent(math::irect2 newExtent);
		void Update(const math::vec2& followObjPos);
		math::TranslateMatrix GetMatrix();

	private:
		math::irect2 extent;
		math::vec2 position;
		math::rect2 movableRange;
	};
}