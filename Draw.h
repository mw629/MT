#include "Calculation.h"


struct Sphere {
	Vector3 center;//íÜêS
	float radius;//îºåa
};

#pragma once
class Draw
{
private:

public:

	void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

	void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);
};

