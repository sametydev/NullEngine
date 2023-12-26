#include <PCH.h>
#include <Component/Object.h>


Object::Object() : id(0), transform()
{
	GUID id{};
	CoCreateGuid(&id);

	mIdStr = Object::GuidToString(id);

	
	wchar_t lpwz[40];
	StringFromGUID2(id, lpwz, 40);

	char str[40] = {};

	WideCharToMultiByte(CP_ACP, 0, lpwz, -1, str, 40, 0, 0);

	std::hash<std::string> hasher;
	uint guid = hasher._Do_hash(mIdStr);
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

std::string Object::GuidToString(const GUID& id)
{
	std::stringstream ss;

	ss << std::hex << std::uppercase << std::setw(8) << std::setfill('0') << id.Data1 << "-" <<
		std::setw(4) << std::setfill('0') << id.Data2 << "-" <<
		std::setw(4) << std::setfill('0') << id.Data3 << "-";

	for (int i = 0; i < std::size(id.Data4); i++)
	{
		if (i == 1)
		{
			ss << std::setw(2) << std::setfill('0') << (int)id.Data4[i] << "-";
		}
		else
		{
			ss << std::setw(2) << std::setfill('0') << (int)id.Data4[i];
		}
	}

	return ss.str();
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
