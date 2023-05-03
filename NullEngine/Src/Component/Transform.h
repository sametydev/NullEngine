#pragma once
class Transform
{
public:
	Transform();

	void SetPosition(const vec3f& position);
	void SetRotation(const vec3f& rotation);
	void SetScale(const vec3f& scale);

	Transform* mParent = nullptr;
	std::vector<Transform> mChild;

	void Update();

	mat4x4 mGlobal;
	mat4x4 mLocal;

	vec3f mPosition;
	vec3f mRotation;
	vec3f mScale;

	union {
		struct { vec3f mAxis[3]; };
		struct { vec3f mRight, mUp, mForward; };
	};

	bool mIsAutoUpdate = false;
};

