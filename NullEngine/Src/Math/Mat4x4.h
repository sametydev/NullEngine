#pragma once
#include <Math/LinearMath.h>

__declspec(align(16))
struct Mat4x4 {
	Mat4x4() {
		SetIdentity();
	};
	Mat4x4(float* rhs) {
		memcpy_s(f, sizeof(f), rhs, sizeof(f));
	};

	Mat4x4(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33
	) {
		m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
		m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
		m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
		m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
	};

	void SetIdentity() {
		memset(f, 0, sizeof(f));
		m[0][0] = 1.f;
		m[1][1] = 1.f;
		m[2][2] = 1.f;
		m[3][3] = 1.f;
	};

	float* data() {
		return f;
	};

	//Static
	static Mat4x4 scaled(const Vec3f& v) {
		Mat4x4 mat = {
		v.x,0.f,0.f,0.f,
		0.f,v.y,0.f,0.f,
		0.f,0.f,v.z,0.f,
		0.f,0.f,0.f,1.f
		};

		return mat;
	};

	union {
		float f[16];
		float m[4][4];
	};
};
