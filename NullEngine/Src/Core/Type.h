#pragma once
#include <Math/LinearMath.h>

//POS ST
struct VertexPS
{
	vec3f position;
	vec2f st;
};

//POS NORMAL ST
struct VertexPNS
{
	vec3f position;
	vec3f normal;
	vec2f st;
};
