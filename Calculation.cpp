#include "Calculation.h"
#include "math.h"
#include "assert.h"

// ベクトル

Vecto3 AddVecto3(Vecto3 v1, Vecto3 v2)
{
	Vecto3 result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}

Vecto3 SubtractVector3(Vecto3 v1, Vecto3 v2)
{
	Vecto3 result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}

Vecto3 MultiplyVector3(Vecto3 v1, Vecto3 v2)
{
	Vecto3 result;
	result.x = v1.x * v2.x;
	result.y = v1.y * v2.y;
	result.z = v1.z * v2.z;
	return result;
}

Vecto3 ScalarMultiply(Vecto3 v, float s)
{
	Vecto3 result;
	result = { v.x * s,v.y * s,v.z * s };
	return result;
}

float Lengeh(Vecto3 v)
{
	float result;
	result = static_cast<float>(sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
	return result;
}

Vecto3 Normalize(Vecto3 v)
{
	Vecto3 result;
	result.x = v.x / Lengeh(v);
	result.y = v.y / Lengeh(v);
	result.z = v.z / Lengeh(v);
	return result;
}

float Dot(Vecto3 v1, Vecto3 v2)
{
	float result;
	result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return result;
}



