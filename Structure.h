#pragma once

struct Vector3 {
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 1.0f;

	Vector3 operator+(const Vector3& other) const { return { x + other.x, y + other.y,z + other.z }; }
	Vector3 operator-(const Vector3& other)  const { return { x - other.x, y - other.y,z - other.z }; }
	Vector3 operator*(float other) const { return { x * other, y * other,z * other }; }
	Vector3 operator/(const Vector3& other) { return { x / other.x, y / other.y ,z / other.z }; }
	Vector3 operator/(float other) { return { x / other, y / other ,z / other }; }
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
	Matrix4x4 operator*(Matrix4x4 other);

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

struct Plane {
	Vector3 normal;//法線
	float distance;//距離
};

struct Line {
	Vector3 origin; //始点
	Vector3 diff;//終点への差分
};

struct Ray {
	Vector3 origin; //始点
	Vector3 diff;//終点への差分
};

struct Segment {
	Vector3 origin; //始点
	Vector3 diff;//終点への差分
};

struct Triangle {
	Vector3 vertices[3];//頂点
};

struct AABB {
	Vector3 min; //最小点
	Vector3 max; //最大点
};
struct BezierCurve {
	Vector3 start;
	Vector3 controlPoint;
	Vector3 end;
};

struct Spring {
	Vector3 anchor;
	float naturalLength;//自然長
	float stiffness;//剛性。ばね定数
};
struct Ball {
	Vector3 postion;//ボールの位置
	Vector3 velosity;//ボールの速度
	Vector3 acceleration;//ボールの加速
	float mass;//ボールの質量
	float radius;//ボールの半径
	unsigned int color;//ボールの色
};