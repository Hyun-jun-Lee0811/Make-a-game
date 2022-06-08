/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Vec2.inl
Author: Hyunjun Lee
Creation date: Spring 2022/4/16
-----------------------------------------------------------------*/
#include "Vec.h"

namespace math
{
	inline constexpr vec2& vec2::operator+=(const vec2& a) noexcept
	{
		this->x = this->x + a.x;
		this->y = this->y + a.y;
		return *this;
	}

	inline constexpr vec2& vec2::operator-=(const vec2& a) noexcept
	{
		this->x = this->x - a.x;
		this->y = this->y - a.y;
		return *this;
	}

	inline constexpr vec2& vec2::operator*=(const vec2& a) noexcept
	{
		this->x = this->x * a.x;
		this->y = this->y * a.y;
		return *this;
	}

	inline constexpr vec2& vec2::operator/=(const vec2& a) noexcept
	{
		this->x = this->x / a.x;
		this->y = this->y / a.y;
		return *this;
	}

	[[nodiscard]] inline constexpr vec2 operator+(const vec2 e, const vec2 f) noexcept
	{
		return vec2(e.x + f.x, e.y + f.y);
	}
	[[nodiscard]] inline constexpr vec2 operator-(const vec2 e, const vec2 f) noexcept
	{
		return vec2(e.x - f.x, e.y - f.y);
	}
	[[nodiscard]] inline constexpr vec2 operator-(const vec2 e) noexcept
	{
		return vec2(-e.x, -e.y);
	}
	[[nodiscard]] inline constexpr vec2 operator*(double e, const vec2 f) noexcept
	{
		return vec2(e * f.x, e * f.y);
	}
	[[nodiscard]] inline constexpr vec2 operator*(const vec2 e, double f) noexcept
	{
		return vec2(e.x * f, e.y * f);
	}
	[[nodiscard]] inline constexpr vec2 operator/(const vec2 e, double f) noexcept
	{
		return vec2(e.x / f, e.y / f);
	}
	[[nodiscard]] constexpr bool operator==(const vec2 e, const vec2 f) noexcept
	{
		return (is_equal(e.x, f.x) == is_equal(e.y, f.y));
	}

	[[nodiscard]] constexpr bool operator!=(const vec2 e, const vec2 f) noexcept
	{
		return (!is_equal(e.x, f.x) || !is_equal(e.y, f.y));
	}
	[[nodiscard]] inline constexpr vec2 operator*(double e, ivec2 f) noexcept
	{
		return vec2(e * f.x, e * f.y);
	}
	[[nodiscard]] inline constexpr vec2 operator*(ivec2 e, double f) noexcept
	{
		return vec2(e.x * f, e.y * f);
	}
	[[nodiscard]] inline constexpr vec2 operator/(ivec2 e, double f) noexcept
	{
		return vec2(e.x / f, e.y / f);
	}

	constexpr  double vec2::LengthSquared() const noexcept
	{
		return ((this->x * this->x) + (this->y * this->y));
	}

	inline vec2 vec2::Normalize() const noexcept
	{
		return *this / sqrt(LengthSquared());
	}

	constexpr  double vec2::Cross(const vec2& v) const noexcept
	{
		return x * v.y - y * v.x;
	}

	//struct ivec2
	inline constexpr ivec2& ivec2::operator+=(const ivec2& b) noexcept
	{
		this->x = this->x + b.x;
		this->y = this->y + b.y;
		return *this;
	}

	inline constexpr ivec2& ivec2::operator-=(const ivec2& b) noexcept
	{
		this->x = this->x - b.x;
		this->y = this->y - b.y;
		return *this;
	}

	inline constexpr ivec2& ivec2::operator*=(const ivec2& b) noexcept
	{
		this->x = this->x * b.x;
		this->y = this->y * b.y;
		return *this;
	}

	inline constexpr ivec2& ivec2::operator/=(const ivec2& b) noexcept
	{
		this->x = this->x / b.x;
		this->y = this->y / b.y;
		return *this;
	}

	[[nodiscard]] inline constexpr ivec2 operator+(const ivec2 n, const ivec2 m) noexcept
	{
		return ivec2(n.x + m.x, n.y + m.y);
	}
	[[nodiscard]] inline constexpr ivec2 operator-(const ivec2 n, const ivec2 m) noexcept
	{
		return ivec2(n.x - m.x, n.y - m.y);

	}
	[[nodiscard]] inline constexpr ivec2 operator-(const ivec2 n) noexcept
	{
		return ivec2(-n.x, -n.y);
	}
	[[nodiscard]] inline constexpr ivec2 operator*(int n, const ivec2 m) noexcept
	{
		return ivec2(n * m.x, n * m.y);
	}
	[[nodiscard]] inline constexpr ivec2 operator*(const ivec2 n, int m) noexcept
	{
		return ivec2(n.x * m, n.y * m);
	}
	[[nodiscard]] inline constexpr ivec2 operator/(const ivec2 n, int m) noexcept
	{
		return ivec2(n.x / m, n.y / m);
	}
	[[nodiscard]] constexpr bool operator==(const ivec2 n, const ivec2 m) noexcept
	{
		return (is_equal(n.x, m.x) == is_equal(n.y, m.y));
	}
	[[nodiscard]] constexpr bool operator!=(const ivec2 n, const ivec2 m) noexcept
	{
		return (!is_equal(n.x, m.x) || !is_equal(n.y, m.y));
	}
}