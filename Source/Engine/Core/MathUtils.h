#pragma once
#include <cmath>

namespace ringo {
	constexpr float Pi = 3.14159f;
	constexpr float TwoPi = 6.28318530718f;
	constexpr float HalfPi = 1.57079632679f;

	constexpr float RadiansToDegrees(float radians) { return radians * (180.0f / Pi); }
	constexpr float DegreesToRadians(float degrees) { return degrees * (Pi / 180.0f); }

	template<typename T>
	inline T Clamp(T value, T min, T max) {
		return (value < min) ? min : (value > max) ? max : value;
	}
}