/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Assignment: CS230 Final Project
File Name: Vec2.h
Author: Hyunjun Lee, Geumbi Yeo
Creation date: Spring 2022/4/16
-----------------------------------------------------------------*/
#pragma once
#include <cmath>
#include <limits>

namespace math
{
	[[nodiscard]] constexpr double abs(double d) noexcept { return (d < 0.0) ? -d : d; }

	[[nodiscard]] constexpr bool is_equal(double d1, double d2) noexcept
	{
		return abs(d1 - d2) <= std::numeric_limits<double>::epsilon() * abs(d1 + d2);
	}
	[[nodiscard]] constexpr bool is_equal(int i1, int i2) noexcept { return i1 == i2; }

	struct vec2
	{
		// TODO
		double x = 0;
		double y = 0;
		constexpr vec2() noexcept = default;
		constexpr vec2(double value1) noexcept : vec2(value1, value1) {}
		constexpr vec2(double value_x1, double value_y1) noexcept : x(value_x1), y(value_y1) {}
		constexpr vec2(int value) noexcept : vec2(static_cast<double> (value)) {}

		constexpr vec2& operator+=(const vec2& a) noexcept;
		constexpr vec2& operator-=(const vec2& a) noexcept;
		constexpr vec2& operator*=(const vec2& a) noexcept;
		constexpr vec2& operator/=(const vec2& a) noexcept;

		constexpr double LengthSquared() const noexcept;
		vec2 Normalize() const noexcept;
		constexpr double Cross(const vec2& v) const noexcept;
	};

	[[nodiscard]] constexpr vec2 operator+(const vec2 e, const vec2 f)noexcept;
	[[nodiscard]] constexpr vec2 operator-(const vec2 e, const vec2 f) noexcept;
	[[nodiscard]] constexpr vec2 operator-(const vec2 e) noexcept;
	[[nodiscard]] constexpr vec2 operator*(double e, const vec2 f) noexcept;
	[[nodiscard]] constexpr vec2 operator*(const vec2 e, double f) noexcept;
	[[nodiscard]] constexpr vec2 operator/(const vec2 e, double f) noexcept;

	[[nodiscard]] constexpr bool operator==(const vec2 e, const vec2 f) noexcept;
	[[nodiscard]] constexpr bool operator!=(const vec2 e, const vec2 f) noexcept;

	struct ivec2
	{
		// TODO
		int x = 0;
		int y = 0;
		constexpr ivec2() noexcept = default;
		constexpr ivec2(int value2) noexcept : ivec2(value2, value2) {}
		constexpr ivec2(int value_x2, int value_y2) noexcept : x(value_x2), y(value_y2) {}

		constexpr ivec2& operator+=(const ivec2& b) noexcept;
		constexpr ivec2& operator-=(const ivec2& b) noexcept;
		constexpr ivec2& operator*=(const ivec2& b) noexcept;
		constexpr ivec2& operator/=(const ivec2& b) noexcept;

		explicit constexpr operator vec2() { return vec2{ static_cast<double>(x),static_cast<double>(y) }; }
		//static_cast<math::vec2>(hotSpot)
	};

	[[nodiscard]] constexpr ivec2 operator+(const ivec2 n, const ivec2 m) noexcept;
	[[nodiscard]] constexpr ivec2 operator-(const ivec2 n, const ivec2 m) noexcept;
	[[nodiscard]] constexpr ivec2 operator-(const ivec2 n) noexcept;
	[[nodiscard]] constexpr ivec2 operator*(int n, const ivec2 m) noexcept;
	[[nodiscard]] constexpr ivec2 operator*(const ivec2 n, int m) noexcept;
	[[nodiscard]] constexpr ivec2 operator/(const ivec2 n, int m) noexcept;

	[[nodiscard]] constexpr bool operator==(const ivec2 n, const ivec2 m) noexcept;
	[[nodiscard]] constexpr bool operator!=(const ivec2 n, const ivec2 m) noexcept;
	[[nodiscard]] constexpr vec2 operator*(double e, const ivec2 f) noexcept;
	[[nodiscard]] constexpr vec2 operator*(const ivec2 e, double f) noexcept;
	[[nodiscard]] constexpr vec2 operator/(const ivec2 e, double f) noexcept;
}

#include "Vec2.inl"