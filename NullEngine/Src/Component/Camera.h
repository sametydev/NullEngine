#pragma once
class Camera
{
	enum Axis {
		Right = 0,Up,Forward
	};
public:
	Camera(float fov, float aspectRatio, float near, float far);

	void SetFOV(float value);
	void SetAspectRatio(float value);
	void Update(float dt);

	void LookAt(const vec3f& eye, const vec3f& target);

	mat4x4& GetViewMatrix();
	mat4x4& GetProjectionMatrix();

	float mFov = 45.f;
	float zNear = 0.01f;
	float zFar = 100.f;
	float mAspect = 0;

	vec3f position;
	vec3f rotation;

	mat4x4 mView;
	mat4x4 mProj;

	vec3f mRight;
	vec3f mUp;
	vec3f mForward;

	float mYaw;
	float mPitch;

};

