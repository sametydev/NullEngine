#pragma once

class Object
{
public:
	Object();
	virtual ~Object();
	//virtual void OnCreate() {};
	//virtual void OnDestroy() {};
	//virtual void OnUpdate() {};


	bool isRenderable = true;

	static std::hash<uint> hasher;

	uint id;

	bool operator == (const Object& other) const {
		return id == other.id;
	}

	std::size_t operator()(const Object& obj) const {
		return hasher(id);
	}
};

class Renderable {
public:
	Renderable();
	virtual ~Renderable();
	virtual void Render();
};

