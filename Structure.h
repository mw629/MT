#pragma once

struct Vector3 {
	float x;
	float y;
	float z;
	float w = 1.0f;

	Vector3 operator+(const Vector3& other) { return { x + other.x, y + other.y,z + other.z }; }
	Vector3 operator-(const Vector3& other) { return { x - other.x, y - other.y,z - other.z }; }
	Vector3 operator*(float other) const { return { x * other, y * other,z * other }; }
	Vector3 operator/(const Vector3& other) { return { x / other.x, y / other.y ,z / other.z }; }
	Vector3 operator=(const Vector3& other) { return { x = other.x, y = other.y,z = other.z }; }
	Vector3 operator+=(const Vector3& other) { return { x += other.x, y += other.y,z += other.z }; }
	Vector3 operator-=(const Vector3& other) { return { x -= other.x, y -= other.y,z -= other.z }; }
	Vector3 operator*=(const Vector3& other) { return { x *= other.x, y *= other.y,z *= other.z }; }
	Vector3 operator/=(const Vector3& other) { return { x /= other.x, y /= other.y,z /= other.z }; }
};

struct Matrix4x4 {
	float m[4][4] = {
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0},
	};

};

struct Camera {
	Vector3 pos;
	Vector3 scale;
	Vector3 rotate;
};
struct Object
{
	Vector3 pos;
	Vector3 scale;
	Vector3 rotate;
};

struct Sphere {
	Vector3 center;//中心
	float radius;//半径
};