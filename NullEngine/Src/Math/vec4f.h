#pragma once
#define NOMINMAX
#include <algorithm>
#undef min
#undef max
#include <assert.h>
#include <ostream>

class vec4f
{
public:
	float x, y, z, w;
	vec4f() : x(0.0), y(0.0), z(0.0), w(0.0) {}
	vec4f(const vec4f& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
	vec4f(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
	explicit vec4f(float f) : x(f), y(f), z(f), w(f) {}

	float& operator[](unsigned int i);
	float operator[](unsigned int i) const;

	vec4f& operator = (const vec4f& v);
	vec4f operator-() const;
	vec4f& operator+=(const vec4f& v);
	vec4f& operator-=(const vec4f& v);
	vec4f& operator*=(const vec4f& v);
	vec4f& operator/=(const vec4f& v);
	vec4f& operator*=(const float& f);
	vec4f& operator/= (const float& f);

	/*----------------- LOCAL -------------------------*/
	float length2() const;
	float length() const;
	float normalize();
	vec4f normalized() const;
	vec4f negative() const;
	inline float dot(const vec4f& v);
	inline vec4f cross(const vec4f& v1, const vec4f& v2);

	/*----------------- STATICS -----------------------*/
	static float dot(const vec4f& v1, const vec4f& v2);
	static float fabsdot(const vec4f& v1, const vec4f& v2);
	static vec4f reflect(const vec4f& dir, const vec4f& n);
	static vec4f min(const vec4f& v1, const vec4f& v2);
	static vec4f max(const vec4f& v1, const vec4f& v2);
	static vec4f lerp(const vec4f& start, const vec4f& end, float factor);

	/*-------------------------------------------------*/
	float maxComponent() const { return std::max(std::max(x, y), z); }
	float minComponent() const { return std::min(std::min(x, y), z); }

	friend std::ostream& operator<<(std::ostream& o, const vec4f& v);
};

inline float& vec4f::operator[](unsigned int i)
{
	assert(i >= 0 && i <= 2);
	return (&x)[i];
}
inline float vec4f::operator[](unsigned int i) const
{
	assert(i >= 0 && i <= 2);
	return (&x)[i];
}

inline vec4f& vec4f::operator=(const vec4f& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
	return *this;
}
inline vec4f vec4f::operator-() const
{
	return vec4f(-x, -y, -z, -w);
}

inline vec4f& vec4f::operator+=(const vec4f& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
	return *this;
}

inline vec4f& vec4f::operator-=(const vec4f& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
	return *this;
}

inline vec4f& vec4f::operator*=(const vec4f& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	w *= v.w;
	return *this;
}

inline vec4f& vec4f::operator/=(const vec4f& v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;
	w /= v.w;
	return *this;
}

inline vec4f& vec4f::operator*=(const float& f)
{
	x *= f;
	y *= f;
	z *= f;
	w *= f;
	return *this;
}

inline vec4f& vec4f::operator/=(const float& f)
{
	float inv = 1.f / f;
	x *= inv;
	y *= inv;
	z *= inv;
	w *= inv;
	return *this;
}

//EXTERNAL OPERATOR

inline vec4f operator+(const vec4f& v1, const vec4f& v2)
{
	return vec4f(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
}

inline vec4f operator-(const vec4f& v1, const vec4f& v2)
{
	return vec4f(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
}

inline vec4f operator*(const vec4f& v1, const vec4f& v2)
{
	return vec4f(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
}

inline vec4f operator*(const vec4f& v, float f)
{
	return vec4f(f * v.x, f * v.y, f * v.z, f * v.w);
}

inline vec4f operator*(float f, const vec4f& v)
{
	return vec4f(f * v.x, f * v.y, f * v.z, f * v.w);
}

inline vec4f operator/(const vec4f& v, float f)
{
	float inv = 1.f / f;
	return vec4f(v.x * inv, v.y * inv, v.z * inv, v.w * inv);
}

inline vec4f operator/(float f, const vec4f& v)
{
	return vec4f(f / v.x, f / v.y, f / v.z, f / v.w);
}

inline vec4f operator/(const vec4f& v1, const vec4f& v2)
{
	return vec4f(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w);
}

inline bool operator==(const vec4f& r, const vec4f& l)
{
	return (r.x == l.x && r.y == l.y && r.z == l.z);
}

inline bool operator!=(const vec4f& r, const vec4f& l)
{
	return (r.x != l.x && r.y != l.y && r.z != l.z);
}

inline bool operator>(const vec4f& r, const vec4f& l)
{
	return (r.length2() > l.length2());
}

inline bool operator<(const vec4f& r, const vec4f& l)
{
	return (r.length2() < l.length2());
}

inline float vec4f::length2() const
{
	return x * x + y * y + z * z + w * w;
}

inline float vec4f::length() const
{
	return std::sqrt(length2());
}

inline float vec4f::normalize()
{
	float len = length(); *this /= len; return len;
}

inline vec4f vec4f::normalized() const
{
	vec4f nor(*this);
	nor.normalize();
	return nor;
}

inline vec4f vec4f::negative() const
{
	return vec4f(-x, -y, -z, -w);
}

inline float vec4f::dot(const vec4f& v)
{
	return x * v.x + y * v.y + z * v.z + w * v.w;
}

inline vec4f vec4f::cross(const vec4f& v1, const vec4f& v2)
{
	float x = v1.y * v2.z - v1.z * v2.y + v1.w * v2.y - v1.y * v2.w;
	float y = v1.z * v2.x - v1.x * v2.z + v1.w * v2.z - v1.z * v2.w;
	float z = v1.x * v2.y - v1.y * v2.x + v1.w * v2.x - v1.x * v2.w;
	float w = v1.x * v2.w - v1.w * v2.x + v1.y * v2.w - v1.w * v2.y;

	return vec4f(x, y, z, w);
}

//STATICS

inline float vec4f::dot(const vec4f& v1, const vec4f& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

inline float vec4f::fabsdot(const vec4f& v1, const vec4f& v2)
{
	return fabs(vec4f::dot(v1, v2));
}


inline vec4f vec4f::reflect(const vec4f& dir, const vec4f& n)
{
	return dir - n * 2 * vec4f::dot(n, dir);
}

inline vec4f vec4f::min(const vec4f& v1, const vec4f& v2)
{
	return vec4f(
		std::min(v1.x, v2.x),
		std::min(v1.y, v2.y),
		std::min(v1.z, v2.z),
		std::min(v1.w, v2.w)
	);
}

inline vec4f vec4f::max(const vec4f& v1, const vec4f& v2)
{
	return vec4f(
		std::max(v1.x, v2.x),
		std::max(v1.y, v2.y),
		std::max(v1.z, v2.z),
		std::max(v1.w, v2.w)
	);
}

inline vec4f vec4f::lerp(const vec4f& start, const vec4f& end, float factor)
{
	return start + (end - start) * factor;
	//return (start + vec4f(factor) * (end - start));
}

inline std::ostream& operator<<(std::ostream& o, const vec4f& v)
{
	o << "vec4( " << v.x << ", " << v.y << " ," << v.z << ')';
	return o;
}