#pragma once
#define NOMINMAX
#include <algorithm>

struct Vec3f
{
	Vec3f() : x(0.0f),y(0.0f),z(0.0){}
	Vec3f(float x) : x(x), y(x), z(x) {}
	Vec3f(float x, float y, float z) : x(x),y(y),z(z) {}

	float x, y, z;
};

