#pragma once
class TCamera
{
	enum Axis {
		Right = 0, Up, Forward
	};
public:
	TCamera(float fov, float aspectRatio, float near, float far);

	void SetFOV(float value);
	void SetAspectRatio(float value);
	void Update(float dt);

	void SetPosition(const vec3f& pos);

	mat4x4 GetViewMatrix();
	mat4x4& GetProjectionMatrix();

	float mFov = 45.f;
	float zNear = 0.01f;
	float zFar = 100.f;
	float mAspect = 0;

	vec3f mPos;
	vec3f mRot;

	mat4x4 mView;
	mat4x4 mProj;

	mat4x4 mLocal;

	vec3f mRight;
	vec3f mUp;
	vec3f mForward;

	float mYaw = 0.0f;
	float mPitch = 0.0f;

};

