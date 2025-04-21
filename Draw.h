
#include <stdint.h>

#include "Calculation.h"

#define M_PI 3.14f

struct Sphere {
	Vector3 center;//���S
	float radius;//���a
};


#pragma once
class Draw
{
public:

	void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

	void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);

};

