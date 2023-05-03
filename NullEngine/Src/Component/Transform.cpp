#include <PCH.h>
#include <Component/Transform.h>
#include <Math/LinearMath.h>

Transform::Transform()
{
	mAxis[0] = vec3f(1.f, 0.f, 0.f);
	mAxis[0] = vec3f(0.f, 1.f, 0.f);
	mAxis[0] = vec3f(0.f, 0.f, 1.f);

	mScale = vec3f(1.0f);
}

void Transform::SetPosition(const vec3f& position)
{
	mPosition = position;
}

void Transform::SetRotation(const vec3f& rotation)
{
	mRotation = rotation;
}

void Transform::SetScale(const vec3f& scale)
{
	mScale = scale;
}

void Transform::Update()
{
	if (!mIsAutoUpdate) return;

	mat4x4 S = mat4x4::scaled(mScale);
	mat4x4 T = mat4x4::translated(mPosition);
	//mat4x4 R = mat4x4::RotationYawPitchRoll(mRotation.x,mRotation.y,mRotation.z);

	mat4x4 rx = mat4x4::RotationAxis(mRight,mRotation.x);
	mat4x4 ry = mat4x4::RotationAxis(mUp, mRotation.y);
	mat4x4 rz = mat4x4::RotationAxis(mForward, mRotation.z);


	mat4x4 R = ry * rx * rz;

	mLocal = S * T * R;


	//NOT GOOD FOR PERFORMANCE ITS TEMPORARY
	if (mParent == nullptr)
	{
		mGlobal = mLocal;
	}

	if (mParent)
	{
		mGlobal = this->mLocal * mParent->mGlobal;
	}

	mLocal = S*T*R;

}
