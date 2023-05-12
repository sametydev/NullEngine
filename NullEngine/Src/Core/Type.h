#pragma once
#include <Math/LinearMath.h>

struct VertexPC
{
	vec3f position;
	vec2f st;
};

struct VertexPNC
{
	vec3f position;
	vec3f normal;
	vec3f color;
};
