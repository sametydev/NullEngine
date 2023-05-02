#pragma once
#define NOMINMAX
#include <algorithm>
#include <iostream>

struct vec3f
{
	vec3f() : x(0.0f),y(0.0f),z(0.0){}
	vec3f(float x) : x(x), y(x), z(x) {}
	vec3f(float x, float y, float z) : x(x),y(y),z(z) {}

	vec3f& operator+=(const vec3f& v);
	vec3f& operator-=(const vec3f& v);
	vec3f& operator*=(const vec3f& v);
	vec3f& operator/=(const vec3f& v);
	bool operator==(const vec3f& v);


	float lenght2() const;
	float lenght() const;
	float dot(const vec3f& v);
	float x, y, z;

	static float dot(const vec3f& v1,const vec3f& v2);
	static vec3f cross(const vec3f& v1, const vec3f& v2);

	friend std::ostream& operator<< (std::ostream& o, const vec3f& v);
};

inline std::ostream& operator<< (std::ostream& o, const vec3f& v) {
	return o << "vec3( " << v.x << ", " << v.y << ", " << v.z << ")";
}

inline vec3f& vec3f::operator+=(const vec3f& v)
{
	x += v.x;
	y += v.y;
	z += v.z;

	return *this;
}

inline vec3f& vec3f::operator-=(const vec3f& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;

	return *this;
}

inline vec3f& vec3f::operator*=(const vec3f& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;

	return *this;
}

inline vec3f& vec3f::operator/=(const vec3f& v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;

	return *this;
}

inline bool vec3f::operator==(const vec3f& v)
{
	return (x == v.x && y == v.y && z == v.z);
}

inline float vec3f::lenght2() const
{
	return (x*x) + (y*y) + (z*z);
}

inline float vec3f::lenght() const
{
	return sqrtf(lenght2()); // == |A|
}

inline float vec3f::dot(const vec3f& v)
{
	// |A| * |B| = Ax * Bx + Ay * By + Az * Bz 
	return x*v.x + y*v.y + z*v.z;
}

inline float vec3f::dot(const vec3f& v1, const vec3f& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline vec3f vec3f::cross(const vec3f& v1, const vec3f& v2)
{
	return vec3f(
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x
	);
}
