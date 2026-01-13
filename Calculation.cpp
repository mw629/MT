#include "Calculation.h"

#include <Novice.h>
#include <cmath>
#include "assert.h"
#include "Collision.h"
#include <algorithm>



//行列、ベクトルの描画

static const int kRowHeight = 20;
static const int kColimnWidth = 60;

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColimnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColimnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColimnWidth * 3, y, "%s", label);
}

void QuaternionScreenPrintf(int x, int y, const Quaternion& quaternion, const char* label)
{
	Novice::ScreenPrintf(x, y, "%.02f", quaternion.x);
	Novice::ScreenPrintf(x + kColimnWidth, y, "%.02f", quaternion.y);
	Novice::ScreenPrintf(x + kColimnWidth * 2, y, "%.02f", quaternion.z);
	Novice::ScreenPrintf(x + kColimnWidth * 3, y, "%.02f", quaternion.w);
	Novice::ScreenPrintf(x + kColimnWidth * 4, y, "%s", label);
}


void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
	Novice::ScreenPrintf(x, y, "%s", label);
	for (int row = 1; row < 5; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(
				x + column * kColimnWidth, y + row * kRowHeight, "%6.02f", matrix.m[row - 1][column]);
		}
	}
}

float AbsValue(float a)
{
	if (a < 0) {
		a *= -1;
	}
	return a;
}




// ベクトル

Vector3 Add(Vector3 v1, Vector3 v2)
{
	Vector3 result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}

Vector3 Subtract(Vector3 v1, Vector3 v2)
{
	Vector3 result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}

Vector3 Multiply(Vector3 v1, Vector3 v2)
{
	Vector3 result;
	result.x = v1.x * v2.x;
	result.y = v1.y * v2.y;
	result.z = v1.z * v2.z;
	return result;
}

Vector3 Multiply(Vector3 v, float s)
{
	Vector3 result;
	result = { v.x * s,v.y * s,v.z * s };
	return result;
}

float Length(Vector3 v)
{
	float result;
	result = static_cast<float>(sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
	return result;
}

Vector3 Normalize(Vector3 v)
{
	Vector3 result{};
	if (Length(v) != 0) {
		result.x = v.x / Length(v);
		result.y = v.y / Length(v);
		result.z = v.z / Length(v);
	}
	return result;
}

float Dot(Vector3 v1, Vector3 v2)
{
	float result;
	result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return result;
}

Vector3 Cross(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return result;
}

Vector3 ProjectionVector(const Vector3& v1, const Vector3& v2)
{
	Vector3 result;
	result = v2 * (Dot(v1, v2) / (Length(v2) * Length(v2)));
	return result;
}

Vector3 ClosestPoint(const Vector3& point, const Segment& segment)
{
	Vector3 result;
	Vector3 o = { point.x - segment.origin.x,point.y - segment.origin.y,point.z - segment.origin.z };
	result.x = segment.origin.x + ProjectionVector(o, segment.diff).x;
	result.y = segment.origin.y + ProjectionVector(o, segment.diff).y;
	result.z = segment.origin.z + ProjectionVector(o, segment.diff).z;
	return result;
}

Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t)
{
	Vector3 vector;
	vector.x = (1 - t) * v1.x + t * v2.x;
	vector.y = (1 - t) * v1.y + t * v2.y;
	vector.z = (1 - t) * v1.z + t * v2.z;
	return vector;
}

float Abs(float x) {
	return (x < 0.0f) ? -x : x;
}




// 行列

Matrix4x4 Add(Matrix4x4 m1, Matrix4x4 m2)//o
{
	Matrix4x4 result;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.m[i][j] = m1.m[i][j] + m2.m[i][j];
		}
	}
	return result;
}

Matrix4x4 Multiply(Matrix4x4 m1, Matrix4x4 m2)//o
{
	Matrix4x4 result;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.m[i][j]
				= m1.m[i][0] * m2.m[0][j]
				+ m1.m[i][1] * m2.m[1][j]
				+ m1.m[i][2] * m2.m[2][j]
				+ m1.m[i][3] * m2.m[3][j];
		}
	}
	return result;
}

Matrix4x4 Transpose(Matrix4x4 m)//o
{
	Matrix4x4 result;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.m[i][j] = m.m[j][i];
		}
	}
	return result;
}

Matrix4x4 Inverse(Matrix4x4 m)
{
	Matrix4x4 result;

	float det
		= m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]
		+ m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]
		+ m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]

		- m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]
		- m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]
		- m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]

		- m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]
		- m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]
		- m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]

		+ m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]
		+ m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]
		+ m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]

		+ m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]
		+ m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]
		+ m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]

		- m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]
		- m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]
		- m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]

		- m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]
		- m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]
		- m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]

		+ m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]
		+ m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]
		+ m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0];

	result.m[0][0] = (m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][1] + m.m[1][3] * m.m[2][1] * m.m[3][2]
		- m.m[1][3] * m.m[2][2] * m.m[3][1] - m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[1][1] * m.m[2][3] * m.m[3][2]) / det;//o

	result.m[0][1] = (-m.m[0][1] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[2][3] * m.m[3][1] - m.m[0][3] * m.m[2][1] * m.m[3][2]
		+ m.m[0][3] * m.m[2][2] * m.m[3][1] + m.m[0][2] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[2][3] * m.m[3][2]) / det;//o

	result.m[0][2] = (m.m[0][1] * m.m[1][2] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[3][1] + m.m[0][3] * m.m[1][1] * m.m[3][2]
		- m.m[0][3] * m.m[1][2] * m.m[3][1] - m.m[0][2] * m.m[1][1] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[3][2]) / det;//o

	result.m[0][3] = (-m.m[0][1] * m.m[1][3] * m.m[2][3] - m.m[0][2] * m.m[1][3] * m.m[2][1] - m.m[0][3] * m.m[1][1] * m.m[2][2]
		+ m.m[0][3] * m.m[1][2] * m.m[2][1] + m.m[0][2] * m.m[1][1] * m.m[2][3] + m.m[0][1] * m.m[1][3] * m.m[2][2]) / det;//o


	result.m[1][0] = (-m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[1][2] * m.m[2][3] * m.m[3][0] - m.m[1][3] * m.m[2][0] * m.m[3][2]
		+ m.m[1][3] * m.m[2][2] * m.m[3][0] + m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[1][0] * m.m[2][3] * m.m[3][2]) / det;//o

	result.m[1][1] = (m.m[0][0] * m.m[2][2] * m.m[3][3] + m.m[0][2] * m.m[2][3] * m.m[3][0] + m.m[0][3] * m.m[2][0] * m.m[3][2]
		- m.m[0][3] * m.m[2][2] * m.m[3][0] - m.m[0][2] * m.m[2][0] * m.m[3][3] - m.m[0][0] * m.m[2][3] * m.m[3][2]) / det;//o

	result.m[1][2] = (-m.m[0][0] * m.m[1][2] * m.m[3][3] - m.m[0][2] * m.m[1][3] * m.m[3][0] - m.m[0][3] * m.m[1][0] * m.m[3][2]
		+ m.m[0][3] * m.m[1][2] * m.m[3][0] + m.m[0][2] * m.m[1][0] * m.m[3][3] + m.m[0][0] * m.m[1][3] * m.m[3][2]) / det;//o

	result.m[1][3] = (m.m[0][0] * m.m[1][2] * m.m[2][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] + m.m[0][3] * m.m[1][0] * m.m[2][2]
		- m.m[0][3] * m.m[1][2] * m.m[2][0] - m.m[0][2] * m.m[1][0] * m.m[2][3] - m.m[0][0] * m.m[1][3] * m.m[2][2]) / det;//o


	result.m[2][0] = (m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][3] * m.m[3][0] + m.m[1][3] * m.m[2][0] * m.m[3][1]
		- m.m[1][3] * m.m[2][1] * m.m[3][0] - m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[1][0] * m.m[2][3] * m.m[3][1]) / det;//o

	result.m[2][1] = (-m.m[0][0] * m.m[2][1] * m.m[3][3] - m.m[0][1] * m.m[2][3] * m.m[3][0] - m.m[0][3] * m.m[2][0] * m.m[3][1]
		+ m.m[0][3] * m.m[2][1] * m.m[3][0] + m.m[0][1] * m.m[2][0] * m.m[3][3] + m.m[0][0] * m.m[2][3] * m.m[3][1]) / det;//o

	result.m[2][2] = (m.m[0][0] * m.m[1][1] * m.m[3][3] + m.m[0][1] * m.m[1][3] * m.m[3][0] + m.m[0][3] * m.m[1][0] * m.m[3][1]
		- m.m[0][3] * m.m[1][1] * m.m[3][0] - m.m[0][1] * m.m[1][0] * m.m[3][3] - m.m[0][0] * m.m[1][3] * m.m[3][1]) / det;//o

	result.m[2][3] = (-m.m[0][0] * m.m[1][1] * m.m[2][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] - m.m[0][3] * m.m[1][0] * m.m[2][0]
		+ m.m[0][3] * m.m[1][1] * m.m[2][0] + m.m[0][1] * m.m[1][0] * m.m[2][3] + m.m[0][0] * m.m[1][3] * m.m[2][1]) / det;//o


	result.m[3][0] = (-m.m[1][0] * m.m[2][1] * m.m[3][2] - m.m[1][1] * m.m[2][2] * m.m[3][0] - m.m[1][2] * m.m[2][0] * m.m[3][1]
		+ m.m[1][2] * m.m[2][1] * m.m[3][0] + m.m[1][1] * m.m[2][0] * m.m[3][2] + m.m[1][0] * m.m[2][2] * m.m[3][1]) / det;//o

	result.m[3][1] = (m.m[0][0] * m.m[2][1] * m.m[3][2] + m.m[0][1] * m.m[2][2] * m.m[3][0] + m.m[0][2] * m.m[2][0] * m.m[3][1]
		- m.m[0][2] * m.m[2][1] * m.m[3][0] - m.m[0][1] * m.m[2][0] * m.m[3][2] - m.m[0][0] * m.m[2][2] * m.m[3][1]) / det;//o

	result.m[3][2] = (-m.m[0][0] * m.m[1][1] * m.m[3][2] - m.m[0][1] * m.m[1][2] * m.m[3][0] - m.m[0][2] * m.m[1][0] * m.m[3][1]
		+ m.m[0][2] * m.m[1][1] * m.m[3][0] + m.m[0][1] * m.m[1][0] * m.m[3][2] + m.m[0][0] * m.m[1][2] * m.m[3][1]) / det;//o

	result.m[3][3] = (m.m[0][0] * m.m[1][1] * m.m[2][2] + m.m[0][1] * m.m[1][2] * m.m[2][0] + m.m[0][2] * m.m[1][0] * m.m[2][1]
		- m.m[0][2] * m.m[1][1] * m.m[2][0] - m.m[0][1] * m.m[1][0] * m.m[2][2] - m.m[0][0] * m.m[1][2] * m.m[2][1]) / det;//o

	return result;
}

Matrix4x4 Multiply(Matrix4x4 m, float s)
{
	Matrix4x4 result;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.m[i][j] = m.m[i][j] * s;
		}
	}
	return result;
}

Vector3 Transform(const Vector3& v, const Matrix4x4& m)
{
	Vector3 result{};

	result.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + m.m[3][0];
	result.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + m.m[3][1];
	result.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + m.m[3][2];
	float w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + m.m[3][3];
	if (w != 0) {
		result.x /= w;
		result.y /= w;
		result.z /= w;
	}
	return result;
}

Matrix4x4 Scale(Vector3 scall)
{
	Matrix4x4 result;

	result.m[0][0] = 1.0f * scall.x;
	result.m[1][1] = 1.0f * scall.y;
	result.m[2][2] = 1.0f * scall.z;
	result.m[3][3] = 1.0f;
	return result;
}

Matrix4x4 RotationX(float angle)
{
	Matrix4x4 result;
	result.m[0][0] = 1.0f;
	result.m[1][1] = std::cos(angle);
	result.m[1][2] = std::sin(angle);
	result.m[2][1] = std::sin(-angle);
	result.m[2][2] = std::cos(angle);
	result.m[3][3] = 1.0f;
	return result;
}

Matrix4x4 RotationY(float angle)
{
	Matrix4x4 result;
	result.m[0][0] = std::cos(angle);
	result.m[0][2] = std::sin(-angle);
	result.m[1][1] = 1.0f;
	result.m[2][0] = std::sin(angle);
	result.m[2][2] = std::cos(angle);
	result.m[3][3] = 1.0f;
	return result;
}

Matrix4x4 RotationZ(float angle)
{
	Matrix4x4 result;
	result.m[0][0] = std::cos(angle);
	result.m[0][1] = std::sin(angle);
	result.m[1][0] = std::sin(-angle);
	result.m[1][1] = std::cos(angle);
	result.m[2][2] = 1.0f;
	result.m[3][3] = 1.0f;
	return result;
}

Matrix4x4 Rotation(Vector3 angle)
{
	Matrix4x4 result;
	result = Multiply(RotationX(angle.x), Multiply(RotationY(angle.y), RotationZ(angle.z)));
	return result;
}

Matrix4x4 MakeRotateAxisAngle(const Vector3& axis, float angle)
{
	Matrix4x4 matrix = IdentityMatrix();
	matrix.m[0][0] = axis.x * axis.x * (1 - cos(angle)) + cos(angle);
	matrix.m[0][1] = axis.x * axis.y * (1 - cos(angle)) + axis.z * sin(angle);
	matrix.m[0][2] = axis.x * axis.z * (1 - cos(angle)) - axis.y * sin(angle);

	matrix.m[1][0] = axis.x * axis.y * (1 - cos(angle)) - axis.z * sin(angle);
	matrix.m[1][1] = axis.y * axis.y * (1 - cos(angle)) + cos(angle);
	matrix.m[1][2] = axis.y * axis.z * (1 - cos(angle)) + axis.x * sin(angle);

	matrix.m[2][0] = axis.x * axis.z * (1 - cos(angle)) + axis.y * sin(angle);
	matrix.m[2][1] = axis.y * axis.z * (1 - cos(angle)) - axis.x * sin(angle);
	matrix.m[2][2] = axis.z * axis.z * (1 - cos(angle)) + cos(angle);

	return matrix;

}

Matrix4x4 DirectionToDirection(const Vector3& from, const Vector3& to) {

	const float EPS = 1e-6f;

	if (Length(from) < EPS || Length(to) < EPS) {
		return IdentityMatrix();
	}

	Vector3 f = Normalize(from);
	Vector3 t = Normalize(to);

	float cos = Dot(f, t);

	cos = std::clamp(cos, -1.0f, 1.0f);

	if (cos > 1.0f - EPS) {
		return IdentityMatrix();
	}
	if (cos < -1.0f + EPS) {
		Vector3 axis = Cross(f, Vector3{ 0.0f,0.0f,1.0f });
		if (Length(axis) < EPS) {
			axis = Cross(f, Vector3({ 0.0f,1.0f,0.0f }));
		}
		axis = Normalize(axis);
		return MakeRotateAxisAngle(axis, 3.14f);
	}

	Vector3 axis = Normalize(Cross(f, t));
	float angle = std::acos(cos);
	return MakeRotateAxisAngle(axis, angle);

}


Matrix4x4 Translation(Vector3 pos)
{
	Matrix4x4 result;
	result.m[0][0] = 1.0f;
	result.m[1][1] = 1.0f;
	result.m[2][2] = 1.0f;
	result.m[3][3] = 1.0f;

	result.m[3][0] = pos.x;
	result.m[3][1] = pos.y;
	result.m[3][2] = pos.z;

	return result;
}

Matrix4x4 IdentityMatrix()
{
	Matrix4x4 m = {
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f };
	return m;
}

Matrix4x4 MakeAffineMatrix(Vector3 pos, Vector3 scale, Vector3 angle)
{
	Matrix4x4 result;
	Matrix4x4 scaleMatrix = Scale(scale);
	Matrix4x4 rotationMatrix = Rotation(angle);
	Matrix4x4 translationMatrix = Translation(pos);

	result.m[0][0] = scaleMatrix.m[0][0] * rotationMatrix.m[0][0];
	result.m[0][1] = scaleMatrix.m[0][0] * rotationMatrix.m[0][1];
	result.m[0][2] = scaleMatrix.m[0][0] * rotationMatrix.m[0][2];

	result.m[1][0] = scaleMatrix.m[1][1] * rotationMatrix.m[1][0];
	result.m[1][1] = scaleMatrix.m[1][1] * rotationMatrix.m[1][1];
	result.m[1][2] = scaleMatrix.m[1][1] * rotationMatrix.m[1][2];

	result.m[2][0] = scaleMatrix.m[2][2] * rotationMatrix.m[2][0];
	result.m[2][1] = scaleMatrix.m[2][2] * rotationMatrix.m[2][1];
	result.m[2][2] = scaleMatrix.m[2][2] * rotationMatrix.m[2][2];

	result.m[3][0] = translationMatrix.m[3][0];
	result.m[3][1] = translationMatrix.m[3][1];
	result.m[3][2] = translationMatrix.m[3][2];
	result.m[3][3] = 1.0f;

	return result;
}

Matrix4x4 MakeOrthographicMatrix(float l, float r, float t, float b, float zn, float zf)
{
	Matrix4x4 result;
	result.m[0][0] = 2.0f / (r - l);
	result.m[1][1] = 2.0f / (t - b);
	result.m[2][2] = 1.0f / (zf - zn);
	result.m[3][0] = (l + r) / (l - r);
	result.m[3][1] = (t + b) / (b - t);
	result.m[3][2] = (zn) / (zn - zf);
	result.m[3][3] = 1.0f;
	return result;
}

Matrix4x4 MakePerspectiveFovMatrix(float fovY, float a, float zn, float zf)
{
	Matrix4x4 result;
	result.m[0][0] = static_cast<float>(1.0f / a * (1.0f / tan(fovY / 2.0f)));
	result.m[1][1] = static_cast<float>(1.0f / tan(fovY / 2.0f));
	result.m[2][2] = static_cast<float>(zf / (zf - zn));
	result.m[2][3] = 1.0f;
	result.m[3][2] = static_cast<float>(-zn * zf / (zf - zn));
	return result;
}

Matrix4x4 MakeViewPortMatrix(float width, float height, float left, float top, float minD, float maxD)
{
	Matrix4x4 result;
	result.m[0][0] = width / 2.0f;
	result.m[1][1] = -height / 2.0f;
	result.m[2][2] = maxD - minD;
	result.m[3][0] = left + width / 2.0f;
	result.m[3][1] = top + height / 2.0f;
	result.m[3][2] = minD;
	result.m[3][3] = 1.0f;
	return result;
}

Quaternion Multiply(const Quaternion& lhs, const Quaternion& rhs)
{
	Quaternion result;

	result.w = lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z;
	result.x = lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y;
	result.y = lhs.w * rhs.y - lhs.x * rhs.z + lhs.y * rhs.w + lhs.z * rhs.x;
	result.z = lhs.w * rhs.z + lhs.x * rhs.y - lhs.y * rhs.x + lhs.z * rhs.w;

	return result;
}

Quaternion IdentityQuaternion()
{
	Quaternion result;

	result.w = 1.0f;
	result.x = 0.0f;
	result.y = 0.0f;
	result.z = 0.0f;

	return result;
}

Quaternion Conjugate(const Quaternion& quaternion)
{
	Quaternion result;

	result.w = quaternion.w;
	result.x = -quaternion.x;
	result.y = -quaternion.y;
	result.z = -quaternion.z;

	return result;
}

float Norm(const Quaternion& quaternion)
{
	return std::sqrt(
		quaternion.w * quaternion.w +
		quaternion.x * quaternion.x +
		quaternion.y * quaternion.y +
		quaternion.z * quaternion.z
	);
}

Quaternion Normalize(const Quaternion& quaternion)
{
	Quaternion result;

	float n = Norm(quaternion);
	if (n < 1e-6f) {
		// ゼロ割防止：回転なしにする
		return IdentityQuaternion();
	}

	result.w = quaternion.w / n;
	result.x = quaternion.x / n;
	result.y = quaternion.y / n;
	result.z = quaternion.z / n;

	return result;
}

Quaternion Inverse(const Quaternion& quaternion)
{
	float n2 =
		quaternion.w * quaternion.w +
		quaternion.x * quaternion.x +
		quaternion.y * quaternion.y +
		quaternion.z * quaternion.z;

	if (n2 < 1e-6f) {
		// 逆が取れんときは回転なし
		return IdentityQuaternion();
	}

	Quaternion result;
	result.w = quaternion.w / n2;
	result.x = -quaternion.x / n2;
	result.y = -quaternion.y / n2;
	result.z = -quaternion.z / n2;

	return result;
}

Quaternion MakeRotateAxisIngleQuternion(const Vector3& axis, float angle)
{
	Quaternion q;

	Vector3 n = Normalize(axis);   // 回転軸は正規化するとよ
	float half = angle * 0.5f;
	float s = sinf(half);

	q.x = n.x * s;
	q.y = n.y * s;
	q.z = n.z * s;
	q.w = cosf(half);

	return q;
}

Vector3 RotateVector(const Vector3& vector, const Quaternion& quaternion)
{
	Quaternion v;
	v.x = vector.x;
	v.y = vector.y;
	v.z = vector.z;
	v.w = 0.0f;

	Quaternion q = quaternion;
	Quaternion qInv = Conjugate(q); // 正規化済み前提たい

	Quaternion r = Multiply(q, Multiply(v, qInv));

	return Vector3{ r.x, r.y, r.z };
}

Matrix4x4 MakeRotateMatrix(const Quaternion& q)
{
	Matrix4x4 m{};

	float xx = q.x * q.x;
	float yy = q.y * q.y;
	float zz = q.z * q.z;
	float xy = q.x * q.y;
	float xz = q.x * q.z;
	float yz = q.y * q.z;
	float wx = q.w * q.x;
	float wy = q.w * q.y;
	float wz = q.w * q.z;

	m.m[0][0] = 1.0f - 2.0f * (yy + zz);
	m.m[0][1] = 2.0f * (xy + wz);
	m.m[0][2] = 2.0f * (xz - wy);
	m.m[0][3] = 0.0f;

	m.m[1][0] = 2.0f * (xy - wz);
	m.m[1][1] = 1.0f - 2.0f * (xx + zz);
	m.m[1][2] = 2.0f * (yz + wx);
	m.m[1][3] = 0.0f;

	m.m[2][0] = 2.0f * (xz + wy);
	m.m[2][1] = 2.0f * (yz - wx);
	m.m[2][2] = 1.0f - 2.0f * (xx + yy);
	m.m[2][3] = 0.0f;

	m.m[3][0] = 0.0f;
	m.m[3][1] = 0.0f;
	m.m[3][2] = 0.0f;
	m.m[3][3] = 1.0f;

	return m;
}
Vector3 Perpendicular(const Vector3& vector)
{
	if (vector.x != 0.0f || vector.y != 0.0f) {
		return{ -vector.y, vector.x, 0.0f };
	}
	return{ 0.0f, -vector.z, vector.y };
}


Vector3 Reflect(const Vector3& input, const Vector3& normal)
{
	Vector3 result;
	result = input - Multiply(normal, (2.0f * Dot(input, normal)));
	return result;
}

void SpringMove(Spring& spring, Ball& ball)
{
	float deltaTime = 1.0f / 60.0f;

	Vector3 diff = ball.shape.center - spring.anchor;
	float length = Length(diff);
	if (length != 0.0f) {
		Vector3 direction = Normalize(diff);
		Vector3 restPostion = spring.anchor + direction * spring.naturalLength;
		Vector3 displacement = Multiply(ball.shape.center - restPostion, length);
		Vector3 restoringForce = Multiply(displacement, -spring.stiffness);
		Vector3 force = restoringForce;
		ball.acceleration = force / ball.mass;
	}
	ball.velosity += ball.acceleration * deltaTime;
	ball.shape.center += ball.velosity * deltaTime;
}

void PendulumMove(Pundulm& pundulm, Sphere& sphere, bool isMove)
{
	float deltaTime = 1.0f / 60.0f;
	if (isMove) {
		pundulm.angularAcceleration = -(9.8f / pundulm.lengrh) * std::sin(pundulm.angle);
		pundulm.angularVelocity += pundulm.angularAcceleration * deltaTime;
		pundulm.angle += pundulm.angularVelocity * deltaTime;
	}
	sphere.center.x = pundulm.anchor.x + std::sin(pundulm.angle) * pundulm.lengrh;
	sphere.center.y = pundulm.anchor.y - std::cos(pundulm.angle) * pundulm.lengrh;
	sphere.center.z = pundulm.anchor.z;
}

void ConicalPendulumMove(ConicalPendulum& conicalPendulum, Sphere& sphere, bool isMove)
{
	float deltaTime = 1.0f / 60.0f;
	if (isMove) {
		conicalPendulum.angularVelocity = std::sqrtf(9.8f / (conicalPendulum.lengrh * std::cos(conicalPendulum.halfApexAngle)));
		conicalPendulum.angle += conicalPendulum.angularVelocity * deltaTime;
	}

	float radius = std::sin(conicalPendulum.halfApexAngle) * conicalPendulum.lengrh;
	float height = std::cos(conicalPendulum.halfApexAngle) * conicalPendulum.lengrh;
	sphere.center.x = conicalPendulum.anchor.x + std::cos(conicalPendulum.angle) * radius;
	sphere.center.y = conicalPendulum.anchor.y - height;
	sphere.center.z = conicalPendulum.anchor.z - std::sin(conicalPendulum.angle) * radius;
}

void BallMove(Ball& ball, Plane& plane, float e)
{
	float deltaTime = 1.0f / 60.0f;
	ball.velosity += ball.acceleration * deltaTime;
	ball.shape.center += ball.velosity * deltaTime;

	if (IsCollision(ball.shape, plane)) {
		Vector3 reflected = Reflect(ball.velosity, plane.normal);
		Vector3 projectToNormal = ProjectionVector(reflected, plane.normal);
		Vector3 movingDirection = reflected - projectToNormal;

		ball.velosity = projectToNormal * e + movingDirection;
	}
}



