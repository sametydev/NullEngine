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

void Camera::SetAspectRatio(float value)
{
	mAspect = value;
}

void Camera::Update(float dt)
{
	float Speed = 5.5f;

	if (Input::IsKeyDown(Key::W))
	{
		position += mForward * Speed * dt;
	}
	if (Input::IsKeyDown(Key::S))
	{
		position -= mForward * Speed * dt;
	}

	float x = -vec3f::dot(mRight, position);
	float y = -vec3f::dot(mUp, position);
	float z = -vec3f::dot(mForward, position);

	mView = {
		mRight.x,mRight.y,mRight.z,x,
		mUp.x,mUp.y,mUp.z,y,
		mForward.x,mForward.y,mForward.z,z,
		0,0,0,1
	};
}

void Camera::LookAt(const vec3f& eye, const vec3f& target)
{
	position = eye;

	mForward = (target - position).normalized();

	mRight = vec3f::cross({0,1,0}, mForward).normalized();

	mUp = vec3f::cross(mForward, mRight).normalized();

	//R-1 = Rt
	//T-1 = Tt

}

mat4x4& Camera::GetViewMatrix()
{
	return mView;
}

mat4x4& Camera::GetProjectionMatrix()
{
	return mProj;
}
