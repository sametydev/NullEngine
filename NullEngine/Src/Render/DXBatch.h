#pragma once
#include <Math/vec4f.h>
class Batch
{
public:
	Batch();
	virtual ~Batch();


	virtual void Init() = 0;

	//Gathering resources
	virtual void Begin() = 0;

	virtual void Render(const char* text, int x, int y,
		const vec4f& color = vec4f(1.f)) = 0;

	virtual void End() = 0;
};