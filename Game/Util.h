#pragma once

#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>

#if defined(__APPLE__)
#include <GLUT/GLUT.h>
#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>
#else
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#include <windows.h>
#endif
#include <GL/glew.h>		// must be downloaded 
#include <GL/freeglut.h>	// must be downloaded unless you have an Apple
#endif

#define PI 3.1415

enum State {
	IDLE, DEAD, JUMP, ATTACK, JUMPATTACK, JUMPSHOOT,
	RUN, SHOOT, SLIDE, RUNSHOOT,
	
	NONE
};

enum ObjectType {
	RUNNING_GIRL, ROBOT, RED_BLOCKING_SQUARE, BACKGROUND,

	TILE
};

const float GRAVITY_MAX = 3;
const float GRAVITY_ACCELERATION = 2;
const float FALLING_CUTOFF = .5f;
const int WINDOW_HEIGHT = 640;
const int WINDOW_WIDTH = 1024;

class Util {
public:
	static void getErrorInfo(unsigned int handle)
	{
		int logLen;
		glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &logLen);
		if (logLen > 0)
		{
			char * log = new char[logLen];
			int written;
			glGetShaderInfoLog(handle, logLen, &written, log);
			printf("Shader log:\n%s", log);
			delete log;
		}
	}

	// check if shader could be compiled
	static void checkShader(unsigned int shader, char * message)
	{
		int OK;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &OK);
		if (!OK)
		{
			printf("%s!\n", message);
			getErrorInfo(shader);
		}
	}

	// check if shader could be linked
	static void checkLinking(unsigned int program)
	{
		int OK;
		glGetProgramiv(program, GL_LINK_STATUS, &OK);
		if (!OK)
		{
			printf("Failed to link shader program!\n");
			getErrorInfo(program);
		}
	}

	static bool gluInvertMatrix(const double m[16], double invOut[16])
	{
		double inv[16], det;
		int i;

		inv[0] = m[5] * m[10] * m[15] -
			m[5] * m[11] * m[14] -
			m[9] * m[6] * m[15] +
			m[9] * m[7] * m[14] +
			m[13] * m[6] * m[11] -
			m[13] * m[7] * m[10];

		inv[4] = -m[4] * m[10] * m[15] +
			m[4] * m[11] * m[14] +
			m[8] * m[6] * m[15] -
			m[8] * m[7] * m[14] -
			m[12] * m[6] * m[11] +
			m[12] * m[7] * m[10];

		inv[8] = m[4] * m[9] * m[15] -
			m[4] * m[11] * m[13] -
			m[8] * m[5] * m[15] +
			m[8] * m[7] * m[13] +
			m[12] * m[5] * m[11] -
			m[12] * m[7] * m[9];

		inv[12] = -m[4] * m[9] * m[14] +
			m[4] * m[10] * m[13] +
			m[8] * m[5] * m[14] -
			m[8] * m[6] * m[13] -
			m[12] * m[5] * m[10] +
			m[12] * m[6] * m[9];

		inv[1] = -m[1] * m[10] * m[15] +
			m[1] * m[11] * m[14] +
			m[9] * m[2] * m[15] -
			m[9] * m[3] * m[14] -
			m[13] * m[2] * m[11] +
			m[13] * m[3] * m[10];

		inv[5] = m[0] * m[10] * m[15] -
			m[0] * m[11] * m[14] -
			m[8] * m[2] * m[15] +
			m[8] * m[3] * m[14] +
			m[12] * m[2] * m[11] -
			m[12] * m[3] * m[10];

		inv[9] = -m[0] * m[9] * m[15] +
			m[0] * m[11] * m[13] +
			m[8] * m[1] * m[15] -
			m[8] * m[3] * m[13] -
			m[12] * m[1] * m[11] +
			m[12] * m[3] * m[9];

		inv[13] = m[0] * m[9] * m[14] -
			m[0] * m[10] * m[13] -
			m[8] * m[1] * m[14] +
			m[8] * m[2] * m[13] +
			m[12] * m[1] * m[10] -
			m[12] * m[2] * m[9];

		inv[2] = m[1] * m[6] * m[15] -
			m[1] * m[7] * m[14] -
			m[5] * m[2] * m[15] +
			m[5] * m[3] * m[14] +
			m[13] * m[2] * m[7] -
			m[13] * m[3] * m[6];

		inv[6] = -m[0] * m[6] * m[15] +
			m[0] * m[7] * m[14] +
			m[4] * m[2] * m[15] -
			m[4] * m[3] * m[14] -
			m[12] * m[2] * m[7] +
			m[12] * m[3] * m[6];

		inv[10] = m[0] * m[5] * m[15] -
			m[0] * m[7] * m[13] -
			m[4] * m[1] * m[15] +
			m[4] * m[3] * m[13] +
			m[12] * m[1] * m[7] -
			m[12] * m[3] * m[5];

		inv[14] = -m[0] * m[5] * m[14] +
			m[0] * m[6] * m[13] +
			m[4] * m[1] * m[14] -
			m[4] * m[2] * m[13] -
			m[12] * m[1] * m[6] +
			m[12] * m[2] * m[5];

		inv[3] = -m[1] * m[6] * m[11] +
			m[1] * m[7] * m[10] +
			m[5] * m[2] * m[11] -
			m[5] * m[3] * m[10] -
			m[9] * m[2] * m[7] +
			m[9] * m[3] * m[6];

		inv[7] = m[0] * m[6] * m[11] -
			m[0] * m[7] * m[10] -
			m[4] * m[2] * m[11] +
			m[4] * m[3] * m[10] +
			m[8] * m[2] * m[7] -
			m[8] * m[3] * m[6];

		inv[11] = -m[0] * m[5] * m[11] +
			m[0] * m[7] * m[9] +
			m[4] * m[1] * m[11] -
			m[4] * m[3] * m[9] -
			m[8] * m[1] * m[7] +
			m[8] * m[3] * m[5];

		inv[15] = m[0] * m[5] * m[10] -
			m[0] * m[6] * m[9] -
			m[4] * m[1] * m[10] +
			m[4] * m[2] * m[9] +
			m[8] * m[1] * m[6] -
			m[8] * m[2] * m[5];

		det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

		if (det == 0)
			return false;

		det = 1.0 / det;

		for (i = 0; i < 16; i++)
			invOut[i] = inv[i] * det;

		return true;
	}

	static State getState(std::string& str){
		if (str == "DEAD") return DEAD;
		if (str == "IDLE") return IDLE;
		if (str == "JUMP") return JUMP;
		if (str == "JUMPATTACK") return JUMPATTACK;
		if (str == "JUMPSHOOT") return JUMPSHOOT;
		if (str == "ATTACK") return ATTACK;
		if (str == "RUN") return RUN;
		if (str == "RUNSHOOT") return RUNSHOOT;
		if (str == "SHOOT") return SHOOT;
		if (str == "SLIDE") return SLIDE;

		throw std::exception("Cannot determine state");
	}
};

// row-major matrix 4x4
struct mat4
{
	float m[4][4];
public:
	mat4() {}

	mat4(double mIn[4][4]) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				m[i][j] = mIn[i][j];
			}
		}
	}

	mat4(float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33)
	{
		m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
		m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
		m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
		m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
	}

	mat4 invert() {
		double majorM[16];
		for (int i = 0; i < 16; i++) {
			majorM[i] = m[i / 4][i % 4];
		}
		double majorI[16];

		bool res = Util::gluInvertMatrix(majorM, majorI);

		if (res == false) {
			exit(1);
		}

		double I[4][4];

		for (int i = 0; i < 16; i++) {
			I[i / 4][i % 4] = majorI[i];
		}

		return mat4(I);
	}

	mat4 operator*(const mat4& right)
	{
		mat4 result;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				result.m[i][j] = 0;
				for (int k = 0; k < 4; k++) result.m[i][j] += m[i][k] * right.m[k][j];
			}
		}
		return result;
	}
	operator float*() { return &m[0][0]; }
};


// 3D point in homogeneous coordinates
struct vec4
{
	float v[4];

	vec4(float x = 0, float y = 0, float z = 0, float w = 1)
	{
		v[0] = x; v[1] = y; v[2] = z; v[3] = w;
	}

	vec4 operator*(const mat4& mat)
	{
		vec4 result;
		for (int j = 0; j < 4; j++)
		{
			result.v[j] = 0;
			for (int i = 0; i < 4; i++) result.v[j] += v[i] * mat.m[i][j];
		}
		return result;
	}

	vec4 operator*(const double scalar) {
		vec4 result;
		for (int j = 0; j < 4; j++) {
			result.v[j] = v[j] * scalar;
		}
		return result;
	}

	vec4 operator+(const vec4& vec)
	{
		vec4 result(v[0] + vec.v[0], v[1] + vec.v[1], v[2] + vec.v[2], v[3] + vec.v[3]);
		return result;
	}
};

// 2D point in Cartesian coordinates
struct vec2
{
	float x, y;

	vec2(float x = 0.0, float y = 0.0) : x(x), y(y) {}

	vec2 operator+(const vec2& v)
	{
		return vec2(x + v.x, y + v.y);
	}

	vec2 operator-(const vec2& v) {
		return vec2(x - v.x, y - v.y);
	}

	vec2 operator*(float s)
	{
		return vec2(x * s, y * s);
	}

	float dot(vec2 v) {
		return v.x * x + v.y * y;
	}
};

struct rectangle {
	vec2 v1;
	vec2 v2;
	vec2 v3;
	vec2 v4;

	rectangle(vec2 v1, vec2 v2, vec2 v3, vec2 v4) 
	: v1(v1), v2(v2), v3(v3), v4(v4){}

	bool collision(rectangle r2) {
		return r2.contains(v1) || r2.contains(v2)
			||r2.contains(v3) || r2.contains(v4);
	}

	bool contains(vec2 p) {
		vec2 V1_V4 = v1 - v4;
		vec2 V3_V4 = v3 - v4;
		vec2 TWO_P_C =  p * 2.0 - v1 - v3;
		return (V3_V4.dot(TWO_P_C - V3_V4) <= 0
			&& V3_V4.dot(TWO_P_C + V3_V4) >= 0
			&& V1_V4.dot(TWO_P_C - V1_V4) <= 0
			&& V1_V4.dot(TWO_P_C + V1_V4) >= 0);
	}

	rectangle operator*(const mat4& mat) {
		vec4 vert1(v1.x, v1.y, 0, 1);
		vec4 vert2(v2.x, v2.y, 0, 1);
		vec4 vert3(v3.x, v3.y, 0, 1);
		vec4 vert4(v4.x, v4.y, 0, 1);

		vec4 modV1 = vert1 * mat;
		vec4 modV2 = vert2 * mat;
		vec4 modV3 = vert3 * mat;
		vec4 modV4 = vert4 * mat;

		return rectangle(
			vec2(modV1.v[0], modV1.v[1]),
			vec2(modV2.v[0], modV2.v[1]),
			vec2(modV3.v[0], modV3.v[1]),
			vec2(modV4.v[0], modV4.v[1])
		);
	}
};

const vec2 CENTER(0, -0.5);
const vec2 LIGHT_CENTER(0, -.2);