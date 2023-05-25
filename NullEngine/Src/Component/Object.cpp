#include <PCH.h>
#include <Component/Object.h>

std::hash<uint> hasher;

Object::Object() : id(0)
{
	static uint idCounter = 0;
	id = idCounter;
	idCounter++;
}

Object::~Object()
{
}

Renderable::Renderable()
{
}

Renderable::~Renderable()
{
}

void Renderable::Render()
{
}
