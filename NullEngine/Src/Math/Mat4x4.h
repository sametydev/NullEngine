#pragma once
#include <Math/LinearMath.h>
# define M_PI			3.14159265358979323846f
# define RADIANS		(M_PI / 180.f)
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
	float* operator[](unsigned int i) {
		return m[i];
	}
	const float* operator[](unsigned int i) const {
		return m[i];
	}
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

	static Mat4x4 translated(const Vec3f& t) {
		Mat4x4 mat = {
		1.f,0.f,0.f,t.x,
		0.f,1.f,0.f,t.y,
		0.f,0.f,1.f,t.z,
		0.f,0.f,0.f,1.f
		};

		return mat;
	}

	//ROTATE Functions;
	static Mat4x4 rotateX(float angle) {
		float theta = angle * RADIANS;
		Mat4x4 mat = {
		1.f,0.f,0.f,0.f,
		0.f,cos(theta),-sin(theta),0.f,
		0.f,sin(theta),cos(theta),0.f,
		0.f,0.f,0.f,1.f
		};

		return mat;
	}
	static Mat4x4 rotateY(float angle) {
		float theta = angle * RADIANS;
		Mat4x4 mat = {
		cos(theta),0.f,sin(theta),0.f,
		0.f,1.f,0.f,0.f,
		-sin(theta),0.f,cos(theta),0.f,
		0.f,0.f,0.f,1.f
		};

		return mat;
	}
	static Mat4x4 rotateZ(float angle) {
		float theta = angle * RADIANS;
		Mat4x4 mat = {
		cos(theta),-sin(theta),0.f,0.f,
		sin(theta),cos(theta),0.f,0.f,
		0.f,0.f,1.f,0.f,
		0.f,0.f,0.f,1.f
		};

		return mat;
	}
	//----------------------------------

	union {
		float f[16];
		float m[4][4];
	};
};


/*

	***** VIEW MATRIX *****
	//Rot-1 == Rot(t)
	<!> ONLY IN ROTATION <!>
	(Col)
	R = {
		4,5
		1,2
	}

	(Row)
	R (-1) = {
		4,1
		5,2
	}

	//T-1 == T(t) == T(xyz-1)
	<!> ONLY IN TRANSFORM <!>
	T = {
		2,3,4
		1,0,6
	}

	T (-1) = {
		2,3,-4
		1,0,-6
	}


	V = T(-1) * R(-1)

	(equals) ==

	V = T(t) * R(t)
	**************************
	
*/