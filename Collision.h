#pragma once
#include "Calculation.h"


bool IsCollision(const Sphere& sphere1, const Sphere& sphere2);
bool IsCollision(const Sphere& sphere, const Plane& plane);
bool IsCollision(const Plane& plane, const Segment& line);
bool IsCollision(const Triangle& triangle, const Segment& line);
bool IsCollision(const AABB& aabb1, const AABB& aabb2);
bool IsCollision(const AABB& aabb, const Sphere& sphere);
bool IsCollision(const AABB& aabb, const Segment& segment);