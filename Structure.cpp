#include "Structure.h"
#include "Calculation.h"

Matrix4x4 Matrix4x4::operator*(Matrix4x4 other)
{
	Matrix4x4 result;
	for (int row = 0; row < 4; ++row) {
		for (int col = 0; col < 4; ++col) {
			result.m[row][col] = 0.0f;
			for (int k = 0; k < 4; ++k) {
				result.m[row][col] += m[row][k] * other.m[k][col];
			}
		}
	}
	return result;
}
