#pragma once
#include <Graphics/DX11/DX11Config.h>
#include <Math/LinearMath.h>

struct VertexPC
{
	vec3f position;
	vec3f color;

	static D3D11_INPUT_ELEMENT_DESC elements[];
	static int nElements;
};

struct VertexPNC
{
	vec3f position;
	vec3f normal;
	vec3f color;
};
