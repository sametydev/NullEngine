#include <PCH.h>
#include <Component/Object.h>

std::hash<uint> hasher;

Object::Object() : id(0), transform()
{
	static uint idCounter = 0;
	id = idCounter;
	idCounter++;
}

Object::~Object()
{
}

Transform* Object::GetTransform()
{
	return transform;
}

void Object::SetTransform(Transform* t)
{
	transform = t;
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
