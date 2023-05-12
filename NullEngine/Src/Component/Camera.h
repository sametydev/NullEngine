#pragma once
class Camera
{
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

	vec3f mAxis[3];
};

