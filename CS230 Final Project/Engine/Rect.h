/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Rect.h
Project: CS230
Author: Hyunjun Lee
Creation date: 2022/4/16 spring
-----------------------------------------------------------------*/
#pragma once
#include "Vec.h"
#include <algorithm>

namespace math
{
	struct [[nodiscard]] rect2
	{
		rect2() = default;
		vec2 point1{ 0.0, 0.0 };
		vec2 point2{ 0.0, 0.0 };

		constexpr vec2 Size() const noexcept { return { Right() - Left(), Top() - Bottom() }; }
		constexpr double Left() const noexcept { return std::min(point1.x, point2.x); }
		constexpr double Right() const noexcept { return std::max(point1.x, point2.x); }
		constexpr double Top() const noexcept { return std::max(point1.y, point2.y); }
		constexpr double Bottom() const noexcept { return std::min(point1.y, point2.y); }
	};

	struct [[nodiscard]] irect2
	{
		irect2() = default;
		ivec2 point1{ 0, 0 };
		ivec2 point2{ 0, 0 };

		constexpr ivec2 Size() const noexcept { return { Right() - Left(), Top() - Bottom() }; }
		constexpr int Left() const noexcept { return std::min(point1.x, point2.x); }
		constexpr int Right() const noexcept { return std::max(point1.x, point2.x); }
		constexpr int Top() const noexcept { return std::max(point1.y, point2.y); }
		constexpr int Bottom() const noexcept { return std::min(point1.y, point2.y); }
	};
}