#pragma once

#include "REAL.h"
#include <math.h>

struct Vec3f
{
	REAL x, y, z;

	Vec3f(REAL _x = 0, REAL _y = 0, REAL _z = 0) : x(_x), y(_y), z(_z) {}

	Vec3f operator + (const Vec3f& v)
	{
		return Vec3f(x + v.x, y + v.y, z + v.z);
	}

	Vec3f operator - (const Vec3f& v)
	{
		return Vec3f(x - v.x, y - v.y, z - v.z);
	}

	Vec3f operator / (const REAL a)
	{
		return Vec3f(x / a, y / a, z / a);
	}

	Vec3f operator * (const REAL a)
	{
		return Vec3f(x * a, y * a, z * a);
	}

	REAL norm()
	{
		return sqrt(x * x + y * y + z * z);
	}

	Vec3f normalization()
	{
		return *this / norm();
	}

	REAL dot(Vec3f& v)
	{
		return x * v.x + y * v.y + z * v.z;
	}

	Vec3f cross(Vec3f& v)
	{
		return Vec3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
};

struct Vec4f
{
	REAL x, y, z, w;

	Vec4f(REAL _x, REAL _y, REAL _z, REAL _w) : x(_x), y(_y), z(_z), w(_w) {}
	
	Vec4f(Vec3f _v, REAL _w) : x(_v.x), y(_v.y), z(_v.z), w(_w) {}
};