#include "Collision.h"
#include <algorithm>

bool IsCollision(const Sphere& sphere1, const Sphere& sphere2) {

	float distance = Lengeh(sphere2.center - sphere1.center);

	if (distance <= sphere1.radius + sphere2.radius) {
		return true;
	}
	return false;
}

bool IsCollision(const Sphere& sphere, const Plane& plane) {

	float distance = AbsValue(Dot(plane.normal, sphere.center) - plane.distance);
	if (distance <= sphere.radius) {
		return true;
	}
	return false;
}

bool IsCollision(const Plane& plane, const Segment& line) {
	float dot = Dot(plane.normal, line.diff);

	if (dot == 0.0f) { return false; }

	float t = (plane.distance - Dot(line.origin, plane.normal)) / dot;

	if (0.0f <= t && t <= 1.0f) {
		return true;
	}
	return false;

}

bool IsCollision(const Triangle& triangle, const Segment& line) {

	Vector3 cross01 = Cross(SubtractVector3(triangle.vertices[0], triangle.vertices[1]), ClosestPoint(triangle.vertices[1], line));
	Vector3 cross02 = Cross(SubtractVector3(triangle.vertices[1], triangle.vertices[2]), ClosestPoint(triangle.vertices[2], line));
	Vector3 cross03 = Cross(SubtractVector3(triangle.vertices[2], triangle.vertices[0]), ClosestPoint(triangle.vertices[0], line));


	Vector3 edge1 = triangle.vertices[1] - triangle.vertices[0];
	Vector3 edge2 = triangle.vertices[2] - triangle.vertices[0];

	Vector3 normal = Cross(edge1, edge2);

	if (Dot(cross01, normal) >= 0.0f &&
		Dot(cross02, normal) >= 0.0f &&
		Dot(cross03, normal) >= 0.0f) {
		return true;
	}
	return false;
}

bool IsCollision(const AABB& aabb1, const AABB& aabb2) {
	if (aabb1.min.x <= aabb2.max.x && aabb1.max.x >= aabb2.min.x &&
		aabb1.min.y <= aabb2.max.y && aabb1.max.y >= aabb2.min.y &&
		aabb1.min.z <= aabb2.max.z && aabb1.max.z >= aabb2.min.z) {
		return true;
	}
	return false;
}


bool IsCollision(const AABB& aabb, const Sphere& sphere) {

	Vector3 closetPoint;

	closetPoint.x = { std::clamp(sphere.center.x,aabb.min.x,aabb.max.x) };
	closetPoint.y = { std::clamp(sphere.center.y,aabb.min.y,aabb.max.y) };
	closetPoint.z = { std::clamp(sphere.center.z,aabb.min.z,aabb.max.z) };

	float distance = Lengeh(closetPoint - sphere.center);

	if (distance <= sphere.radius) {
		return true;
	}


	return false;
}

bool IsCollision(const AABB& aabb, const Segment& segment)
{
	Vector3 t1;
	Vector3 t2;
	Vector3 tNear;
	Vector3 tFar;

	t1.x = (aabb.min.x - segment.origin.x) / segment.diff.x;
	t2.x = (aabb.max.x - segment.origin.x) / segment.diff.x;
	t1.y = (aabb.min.y - segment.origin.y) / segment.diff.y;
	t2.y = (aabb.max.y - segment.origin.y) / segment.diff.y;
	t1.z = (aabb.min.z - segment.origin.z) / segment.diff.z;
	t2.z = (aabb.max.z - segment.origin.z) / segment.diff.z;

	tNear.x = std::min(t1.x, t2.x);
	tFar.x = std::max(t1.x, t2.x);
	tNear.y = std::min(t1.y, t2.y);
	tFar.y = std::max(t1.y, t2.y);
	tNear.z = std::min(t1.z, t2.z);
	tFar.z = std::max(t1.z, t2.z);

	float tmin = std::max(std::max(tNear.x, tNear.y), tNear.z);

	float tmax = std::min(std::min(tFar.x, tFar.y), tFar.z);

	if (tmin <= tmax && tmax >= 0.0f && tmin <= 1.0f) {
		return true;
	}

	return false;
}


