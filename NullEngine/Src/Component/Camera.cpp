#include <PCH.h>
#include <Component/Camera.h>

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
}

void Camera::LookAt(const vec3f& eye, const vec3f& target)
{
	position = eye;

	//mAxis[0] = FORWARD
	//mAxis[1] = UP
	//mAxis[2] = RIGHT

	mAxis[0] = (target - position).normalized();

	mAxis[2] = vec3f::cross({0,1,0}, mAxis[0]).normalized();

	mAxis[1] = vec3f::cross(mAxis[0], mAxis[2]).normalized();


	float x = -vec3f::dot(mAxis[2], position);
	float y = -vec3f::dot(mAxis[1], position);
	float z = -vec3f::dot(mAxis[0], position);

	mView = {
		mAxis[2].x,mAxis[2].y,mAxis[2].z,x,
		mAxis[1].x,mAxis[1].y,mAxis[1].z,y,
		mAxis[0].x,mAxis[0].y,mAxis[0].z,z,
		0,0,0,1
	};

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
