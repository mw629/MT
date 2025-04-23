#include "Calculation.h"


struct Sphere {
	Vector3 center;//���S
	float radius;//���a
};

#pragma once
class Draw
{
private:

public:

	void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

	void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);
};

