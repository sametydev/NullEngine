#include <PCH.h>
#include <Component/Camera.h>
#include <Engine/Input.h>

Camera::Camera(float fov, float aspectRatio, float near, float far)
{
	mFov = fov;
	zNear = near;
	zFar = far;
	mAspect = aspectRatio;

	mProj = mat4x4::perspectiveLH(mFov, mAspect, zNear, zFar);
}

void Camera::SetFOV(float value)
{
	mFov = value;
}

void Camera::Update(float dt)
{
	//if (Input::IsKeyDown(Key::W))
	//{
	//	position += forward * keySpeed * dt;
	//}
	//if (Input::IsKeyDown(Key::S))
	//{
	//	position -= forward * keySpeed * dt;
	//}

	//if (Input::IsKeyDown(Key::D))
	//{
	//	position += right * keySpeed * dt;
	//}
	//if (Input::IsKeyDown(Key::A))
	//{
	//	position -= right * keySpeed * dt;
	//}
}

void Camera::LookAt(const vec3f& target)
{
	vec3f forward = (target - position).normalized();

	vec3f up = {};
}

mat4x4& Camera::GetViewMatrix()
{
	return mView;
}

mat4x4& Camera::GetProjectionMatrix()
{
	return mProj;
}
