#pragma once
#include <Math/LinearMath.h>
#include <iomanip>


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
	vec3f operator*(const vec3f& v);

	void SetIdentity();

	float* data();
	float* operator[](unsigned int i);
	const float* operator[](unsigned int i) const;

	mat4x4 inverted();

	static mat4x4 transposed(const mat4x4& m);
	static mat4x4 transposedTranslation(const mat4x4& rhs);
	//Static
	static mat4x4 scaled(const vec3f& v);

	static mat4x4 translated(const vec3f& t);

	//ROTATE Functions;
	static mat4x4 rotateX(float angle);
	static mat4x4 rotateY(float angle);
	static mat4x4 rotateZ(float angle);
	//----------------------------------

	static mat4x4 perspectiveLH(float fovY, float ratioX, float znear, float zfar);
	static mat4x4 LookAt(const vec3f& pos, const vec3f& center, const vec3f& worldUp);
	static mat4x4 RotationYawPitchRoll(float yaw, float pitch, float roll);
	static mat4x4 RotationAxis(const vec3f& v, float angle);

	union {
		float f[16];
		float m[4][4];
	};

};

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

inline mat4x4 mat4x4::inverted()
{
	float inv[16] = {};
	float det = 0.0f;
	int i;

	inv[0] = f[5] * f[10] * f[15] -
		f[5] * f[11] * f[14] -
		f[9] * f[6] * f[15] +
		f[9] * f[7] * f[14] +
		f[13] * f[6] * f[11] -
		f[13] * f[7] * f[10];

	inv[4] = -f[4] * f[10] * f[15] +
		f[4] * f[11] * f[14] +
		f[8] * f[6] * f[15] -
		f[8] * f[7] * f[14] -
		f[12] * f[6] * f[11] +
		f[12] * f[7] * f[10];

	inv[8] = f[4] * f[9] * f[15] -
		f[4] * f[11] * f[13] -
		f[8] * f[5] * f[15] +
		f[8] * f[7] * f[13] +
		f[12] * f[5] * f[11] -
		f[12] * f[7] * f[9];

	inv[12] = -f[4] * f[9] * f[14] +
		f[4] * f[10] * f[13] +
		f[8] * f[5] * f[14] -
		f[8] * f[6] * f[13] -
		f[12] * f[5] * f[10] +
		f[12] * f[6] * f[9];

	inv[1] = -f[1] * f[10] * f[15] +
		f[1] * f[11] * f[14] +
		f[9] * f[2] * f[15] -
		f[9] * f[3] * f[14] -
		f[13] * f[2] * f[11] +
		f[13] * f[3] * f[10];

	inv[5] = f[0] * f[10] * f[15] -
		f[0] * f[11] * f[14] -
		f[8] * f[2] * f[15] +
		f[8] * f[3] * f[14] +
		f[12] * f[2] * f[11] -
		f[12] * f[3] * f[10];

	inv[9] = -f[0] * f[9] * f[15] +
		f[0] * f[11] * f[13] +
		f[8] * f[1] * f[15] -
		f[8] * f[3] * f[13] -
		f[12] * f[1] * f[11] +
		f[12] * f[3] * f[9];

	inv[13] = f[0] * f[9] * f[14] -
		f[0] * f[10] * f[13] -
		f[8] * f[1] * f[14] +
		f[8] * f[2] * f[13] +
		f[12] * f[1] * f[10] -
		f[12] * f[2] * f[9];

	inv[2] = f[1] * f[6] * f[15] -
		f[1] * f[7] * f[14] -
		f[5] * f[2] * f[15] +
		f[5] * f[3] * f[14] +
		f[13] * f[2] * f[7] -
		f[13] * f[3] * f[6];

	inv[6] = -f[0] * f[6] * f[15] +
		f[0] * f[7] * f[14] +
		f[4] * f[2] * f[15] -
		f[4] * f[3] * f[14] -
		f[12] * f[2] * f[7] +
		f[12] * f[3] * f[6];

	inv[10] = f[0] * f[5] * f[15] -
		f[0] * f[7] * f[13] -
		f[4] * f[1] * f[15] +
		f[4] * f[3] * f[13] +
		f[12] * f[1] * f[7] -
		f[12] * f[3] * f[5];

	inv[14] = -f[0] * f[5] * f[14] +
		f[0] * f[6] * f[13] +
		f[4] * f[1] * f[14] -
		f[4] * f[2] * f[13] -
		f[12] * f[1] * f[6] +
		f[12] * f[2] * f[5];

	inv[3] = -f[1] * f[6] * f[11] +
		f[1] * f[7] * f[10] +
		f[5] * f[2] * f[11] -
		f[5] * f[3] * f[10] -
		f[9] * f[2] * f[7] +
		f[9] * f[3] * f[6];

	inv[7] = f[0] * f[6] * f[11] -
		f[0] * f[7] * f[10] -
		f[4] * f[2] * f[11] +
		f[4] * f[3] * f[10] +
		f[8] * f[2] * f[7] -
		f[8] * f[3] * f[6];

	inv[11] = -f[0] * f[5] * f[11] +
		f[0] * f[7] * f[9] +
		f[4] * f[1] * f[11] -
		f[4] * f[3] * f[9] -
		f[8] * f[1] * f[7] +
		f[8] * f[3] * f[5];

	inv[15] = f[0] * f[5] * f[10] -
		f[0] * f[6] * f[9] -
		f[4] * f[1] * f[10] +
		f[4] * f[2] * f[9] +
		f[8] * f[1] * f[6] -
		f[8] * f[2] * f[5];

	det = f[0] * inv[0] + f[1] * inv[4] + f[2] * inv[8] + f[3] * inv[12];

	if (det == 0)
		return mat4x4();

	det = 1.0f / det;

	mat4x4 mat{};
	for (i = 0; i < 16; i++)
		mat.f[i] = inv[i] * det;

	return mat;
}

inline vec3f mat4x4::operator*(const vec3f& v)
{
	float x, y, z;

	x =			(v.x * m[0][0]) + (v.y * m[0][1]) + (v.z * m[0][2]) + m[0][1];
	y =			(v.x * m[1][0]) + (v.y * m[1][1]) + (v.z * m[1][2]) + m[1][1];
	z =			(v.x * m[2][0]) + (v.y * m[2][1]) + (v.z * m[2][2]) + m[2][1];
	float w =   (v.x * m[3][0]) + (v.y * m[3][1]) + (v.z * m[3][2]) + m[3][1];

	x /= w;
	y /= w;
	z /= w;

	return vec3f(x,y,z);
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

inline mat4x4 mat4x4::transposedTranslation(const mat4x4& rhs)
{
	mat4x4 mat;
	mat[0][3] = rhs[0][3] * -1.f;
	mat[1][3] = rhs[1][3] * -1.f;
	mat[2][3] = rhs[2][3] * -1.f;

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
		0.f,0.f,  C,  D,
		0.f,0.f,  E,0.f
	};

	return mat;
}

inline mat4x4 mat4x4::LookAt(const vec3f& pos, const vec3f& center, const vec3f& worldUp)
{
	vec3f f = (center-pos).normalized();
	vec3f r   = vec3f::cross(worldUp , f).normalized();
	vec3f u      = vec3f::cross(f, r).normalized();

	float x = -vec3f::dot(r,pos);
	float y = -vec3f::dot(u, pos);
	float z = -vec3f::dot(f, pos);

	mat4x4 m = {
		r.x,r.y,r.z,x,
		u.x,u.y,u.y,y,
		f.x,f.y,f.z,z,
		0,0,0,1
	};

	return m;
}

inline mat4x4 mat4x4::RotationYawPitchRoll(float yaw, float pitch, float roll)
{
	//https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles

	//          yaw               pitch                roll
	// |  cosy   0  siny     1      0      0  |     | cosz  -sinz    0 |
	// |     0   1     0  *  0   cosx  -sinx  |  *  | sinz   cosz    0 |
	// | -siny   0  cosy     0   sinx   cosx  |     |    0      0    1 |
	//
	//            (yaw * pitch)                       roll
	// |  cosy   siny*sinx   siny*cosx  |     | cosz  -sinz    0 |
	// |   0     cosx       -sinx	    |  *  | sinz   cosz    0 |
	// | -siny   cosy*sinx   cosy*cosx  |     |    0      0    1 |
	//
	//							Yaw * Pitch * Roll
	// | cosy*cosz + siny*sinx *sinz   cosy*-sinz+ siny*sinx*cosz   siny*cosx |
	// | cosx*sinz                     cosx*cosz                    -sinx	  |
	// | -siny*cosz+cosy*sinx*sinz     -siny*-sinz+cosy*sinx*cosz   cosy*cosx |

	yaw *= RADIANS;
	pitch *= RADIANS;
	roll *= RADIANS;

	float cosx = cos(pitch);
	float cosy = cos(yaw);
	float cosz = cos(roll);
	float sinx = sin(pitch);
	float siny = sin(yaw);
	float sinz = sin(roll);

	mat4x4 mat = {
			cosy * cosz + siny * sinx * sinz,  cosy * -sinz + siny * sinx * cosz,  siny * cosx,  0.0f,
			cosx * sinz,                    cosx * cosz,                    -sinx,      0.0f,
			-siny * cosz + cosy * sinx * sinz,  -siny * -sinz + cosy * sinx * cosz, cosy * cosx,  0.0f,
			0.0f,                         0.0f,                         0.0f,       1.0f
	};

	return mat;
}

inline mat4x4 mat4x4::RotationAxis(const vec3f& v, float angle)
{
	float theta = angle * RADIANS;
	float cosx = cos(v.x * theta);
	float cosy = cos(v.y * theta);
	float cosz = cos(v.z * theta);
	float sinx = sin(v.x * theta);
	float siny = sin(v.y * theta);
	float sinz = sin(v.z * theta);

	mat4x4 mat = {
		cosy * cosz + siny * sinx * sinz,  cosy * -sinz + siny * sinx * cosz,  siny * cosx,  0.0f,
		cosx * sinz,                    cosx * cosz,                    -sinx,      0.0f,
		-siny * cosz + cosy * sinx * sinz,  -siny * -sinz + cosy * sinx * cosz, cosy * cosx,  0.0f,
		0.0f,                         0.0f,                         0.0f,       1.0f
	};
	return mat;
}

inline std::ostream& operator<<(std::ostream& o, const mat4x4& mat) {
#define FM std::setw(12)
	//row major order
	o << "mat4x4[" << "\n" <<
		FM << mat[0][0] << FM << mat[0][1] << FM << mat[0][2] << FM << mat[0][3] << "\n" <<
		FM << mat[1][0] << FM << mat[1][1] << FM << mat[1][2] << FM << mat[1][3] << "\n" <<
		FM << mat[2][0] << FM << mat[2][1] << FM << mat[2][2] << FM << mat[2][3] << "\n" <<
		FM << mat[3][0] << FM << mat[3][1] << FM << mat[3][2] << FM << mat[3][3] << " ]" << "\n";
#undef FM
	return o;
}