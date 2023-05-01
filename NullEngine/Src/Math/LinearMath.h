#pragma once
#define NOMINMAX
#include <algorithm>
#include <iostream>

struct Vec3f
{
	Vec3f() : x(0.0f),y(0.0f),z(0.0){}
	Vec3f(float x) : x(x), y(x), z(x) {}
	Vec3f(float x, float y, float z) : x(x),y(y),z(z) {}

	float x, y, z;


	friend std::ostream& operator<< (std::ostream& o, const Vec3f& v);
};

inline std::ostream& operator<< (std::ostream& o, const Vec3f& v) {
	return o << "vec3( " << v.x << ", " << v.y << ", " << v.z << ")";
}

