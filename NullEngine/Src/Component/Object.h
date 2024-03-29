#pragma once
#include <Component/Transform.h>
#include <string>
#include <sstream>
#include <guiddef.h>
#include <combaseapi.h>


class Object
{
public:
	Object();
	virtual ~Object();

	virtual void OnCreate() {};
	virtual void OnDestroy() {};
	virtual void OnUpdate() {};

	Transform* GetTransform();

	void SetTransform(Transform* t);

	uint id;
	

	static std::string GuidToString(const GUID& id);

	std::string& GetGUID() { return this->mIdStr; };

private:
	Transform* transform;

	std::string mIdStr;
};

class Renderable {
public:
	Renderable();
	virtual ~Renderable();
	virtual void Render();
};
