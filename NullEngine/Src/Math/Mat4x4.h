#pragma once
#include <Math/LinearMath.h>
# define M_PI			3.14159265358979323846f
# define RADIANS		(M_PI / 180.f)


__declspec(align(16))
struct mat4x4 {
	//static float radians = 3.14159265358979323846f / 180.f;
	mat4x4();
	mat4x4(float* rhs);

	mat4x4(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33
	);

	mat4x4 operator*(const mat4x4& rhs);

	void SetIdentity();

	float* data();
	float* operator[](unsigned int i);
	const float* operator[](unsigned int i) const;

	static mat4x4 transposed(const mat4x4& m);

	//Static
	static mat4x4 scaled(const vec3f& v);

	static mat4x4 translated(const vec3f& t);

	//ROTATE Functions;
	static mat4x4 rotateX(float angle);
	static mat4x4 rotateY(float angle);
	static mat4x4 rotateZ(float angle);
	//----------------------------------

	static mat4x4 perspectiveLH(float fovY, float ratioX, float znear, float zfar);

	union {
		float f[16];
		float m[4][4];
	};

};


/*


	{        
		1,2
		3,4
	}

	{
		1,2
		4,5
	}

	1*1 + 2*4, 1*2 + 2*5
	3*1 + 4*4, 3*2 + 4*5


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

inline mat4x4::mat4x4() {
	SetIdentity();
};
inline mat4x4::mat4x4(float* rhs) {
	memcpy_s(f, sizeof(f), rhs, sizeof(f));
};

inline mat4x4::mat4x4(
	float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33
) {
	m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
	m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
	m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
	m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
}

inline mat4x4 mat4x4::operator*(const mat4x4& rhs) {
	mat4x4 mat;
	//00 01 02 03          //00 01 02 03
	//10 11 12 13		   //10 11 12 13
	//20 21 22 23		   //20 21 22 23
	//30 31 32 33		   //30 31 32 33

	//mat[0][0] = mat[0][0] * rhs[0][0] +
	//			  mat[0][1] * rhs[1][0] +
	//			  mat[0][2] * rhs[2][0] +
	//			  mat[0][3] * rhs[3][0];

	//mat[1][0] = mat[1][0] * rhs[0][1] +
	//			  mat[1][1] * rhs[1][1] +
	//			  mat[1][2] * rhs[2][1] +
	//			  mat[1][3] * rhs[3][1];


	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			mat[row][col] = m[row][0] * rhs[0][col] +
				m[row][1] * rhs[1][col] +
				m[row][2] * rhs[2][col] +
				m[row][3] * rhs[3][col];
		}
	}
	return mat;
}

inline void mat4x4::SetIdentity() {
	memset(f, 0, sizeof(f));
	m[0][0] = 1.f;
	m[1][1] = 1.f;
	m[2][2] = 1.f;
	m[3][3] = 1.f;
};

inline float* mat4x4::data() {
	return f;
};
inline float* mat4x4::operator[](unsigned int i) {
	return m[i];
}
inline const float* mat4x4::operator[](unsigned int i) const {
	return m[i];
}

inline mat4x4 mat4x4::transposed(const mat4x4& m) {
	mat4x4 mat = {
		m[0][0],m[1][0],m[2][0],m[3][0],
		m[0][1],m[1][1],m[2][1],m[3][1],
		m[0][2],m[1][2],m[2][2],m[3][2],
		m[0][3],m[1][3],m[2][3],m[3][3]
	};

	return mat;
}

//Static
inline mat4x4 mat4x4::scaled(const vec3f& v) {
	mat4x4 mat = {
	v.x,0.f,0.f,0.f,
	0.f,v.y,0.f,0.f,
	0.f,0.f,v.z,0.f,
	0.f,0.f,0.f,1.f
	};

	return mat;
};

inline mat4x4 mat4x4::translated(const vec3f& t) {
	mat4x4 mat = {
	1.f,0.f,0.f,t.x,
	0.f,1.f,0.f,t.y,
	0.f,0.f,1.f,t.z,
	0.f,0.f,0.f,1.f
	};

	return mat;
}

//ROTATE Functions;
inline mat4x4 mat4x4::rotateX(float angle) {
	float theta = angle * RADIANS;
	mat4x4 mat = {
	1.f,0.f,0.f,0.f,
	0.f,cos(theta),-sin(theta),0.f,
	0.f,sin(theta),cos(theta),0.f,
	0.f,0.f,0.f,1.f
	};

	return mat;
}
inline mat4x4 mat4x4::rotateY(float angle) {
	float theta = angle * RADIANS;
	mat4x4 mat = {
	cos(theta),0.f,sin(theta),0.f,
	0.f,1.f,0.f,0.f,
	-sin(theta),0.f,cos(theta),0.f,
	0.f,0.f,0.f,1.f
	};

	return mat;
}
inline mat4x4 mat4x4::rotateZ(float angle) {
	float theta = angle * RADIANS;
	float sinx = sin(theta);
	float cosx = cos(theta);
	mat4x4 mat = {
	cosx,-sinx,0.f,0.f,
	sinx,cosx,0.f,0.f,
	0.f,0.f,1.f,0.f,
	0.f,0.f,0.f,1.f
	};

	return mat;
}
//----------------------------------

inline mat4x4 mat4x4::perspectiveLH(float fovY, float ratioX, float znear, float zfar)
{
	float halfFov = fovY * 0.5f;
	const float tanFov = std::tan(RADIANS * halfFov);

	float A = 1.f / (ratioX * tanFov);
	float B = 1.f / tanFov;
	float C = zfar / (zfar - znear);
	float D = (-znear * zfar) / (zfar - znear);
	float E = 1.f;

	mat4x4 mat = {
		  A,0.f,0.f,0.f,
		0.f,  B,0.f,0.f,
		0.f,0.f,  C,  E,
		0.f,0.f,  D,0.f
	};

	return mat;
}