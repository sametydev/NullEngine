#include <PCH.h>
#include <Component/TCamera.h>
#include <Engine/Input.h>

TCamera::TCamera(float fov, float aspectRatio, float near, float far)
{
	mFov = fov;
	zNear = near;
	zFar = far;
	mAspect = aspectRatio;

	mProj = mat4x4::perspectiveLH(mFov, mAspect, zNear, zFar);
}

void TCamera::SetFOV(float value)
{
	mFov = value;
}

void TCamera::SetAspectRatio(float value)
{
	mAspect = value;
}

void TCamera::Update(float dt)
{
	constexpr float movementSpeed = 6.6f;
	constexpr float mouseSpeed = 26.6f;

	if (Input::IsKeyDown(Key::LMB)) {
		vec2f delta = Input::delta;
		mRot.y += delta.x * mouseSpeed * dt;
		mRot.x += delta.y * mouseSpeed * dt;
	}

	mat4x4 R = mat4x4::RotationYawPitchRoll(mRot.y, mRot.x, mRot.z);
	//right
	vec3f r = { R[0][0], R[1][0], R[2][0] };
	//up
	vec3f u = { R[0][1], R[1][1], R[2][1] };
	//foward
	vec3f f = { R[0][2], R[1][2], R[2][2] };
	r.normalize();
	u.normalize();
	f.normalize();

	if (Input::IsKeyDown(Key::W)) {
		mPos += f * movementSpeed * dt;
	}
	if (Input::IsKeyDown(Key::S)) {
		mPos -= f * movementSpeed * dt;
	}
	if (Input::IsKeyDown(Key::D)) {
		mPos += r * movementSpeed * dt;
	}
	if (Input::IsKeyDown(Key::A)) {
		mPos -= r * movementSpeed * dt;
	}

	mLocal = {
		r.x, u.x, f.x, mPos.x,
		r.y, u.y, f.y, mPos.y,
		r.z, u.z, f.z, mPos.z,
		0.f, 0.f, 0.f, 1.0f
	};
}

void TCamera::SetPosition(const vec3f& pos)
{
	mPos = pos;
}



mat4x4 TCamera::GetViewMatrix()
{
	return mLocal.inverted();
}

mat4x4& TCamera::GetProjectionMatrix()
{
	return mProj;
}
