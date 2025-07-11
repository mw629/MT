#include "Calculation.h"

#include <Novice.h>
#include <cmath>
#include "assert.h"



//行列、ベクトルの描画

static const int kRowHeight = 20;
static const int kColimnWidth = 60;

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColimnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColimnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColimnWidth * 3, y, "%s", label);
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

float Lengeh(Vector3 v)
{
	float result;
	result = static_cast<float>(sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
	return result;
}

Vector3 Normalize(Vector3 v)
{
	Vector3 result{};
	if (Lengeh(v) != 0) {
		result.x = v.x / Lengeh(v);
		result.y = v.y / Lengeh(v);
		result.z = v.z / Lengeh(v);
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
	result = v2 * (Dot(v1, v2) / (Lengeh(v2) * Lengeh(v2)));
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

Vector3 Perpendicular(const Vector3& vector)
{
	if (vector.x != 0.0f || vector.y != 0.0f) {
		return{ -vector.y, vector.x, 0.0f };
	}
	return{ 0.0f, -vector.z, vector.y };
}

void SpringMove(Spring& spring, Ball& ball)
{
	float deltaTime = 1.0f / 60.0f;

	Vector3 diff = ball.shape.center - spring.anchor;
	float length = Lengeh(diff);
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



