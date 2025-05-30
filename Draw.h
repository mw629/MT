#include "Calculation.h"
#include "Structure.h"



#pragma once
class Draw
{
private:

	float width= 1280.0f;  
	float height= 720.0f;
	float left=0.0f;
	float top=0.0f;
	float minD=0.0f;
	float maxD= 1.0f;


	Matrix4x4 cameraMatrix;
	Matrix4x4 viewMatrix;
	Matrix4x4 projectionMatrix;
	Matrix4x4 viewportMatrix = MakeViewPortMatrix(width, height, left, top, minD, maxD);



public:

	//球の描画
	void DrawSphere(const Sphere& sphere, Camera camera,uint32_t color);
	//グリッドの描画
	void DrawGrid(Camera camera);
	//平面の描画
	void DrawPlane(const Plane& plane, Camera camera, uint32_t color);
	//線の描画
	void DrawLine(const Segment& line, Camera camera, uint32_t color);
	//三角形の描画
	void DrawTriangle(const Triangle& triangle, Camera camera, uint32_t color, FillMode fillMode);
	//AABBの描画
	void DrawAABB(const AABB& aabb, Camera camera, uint32_t color);

	Matrix4x4 MakeprojectionMatrix(Camera camera);

	Matrix4x4 Renderingpipeline(Camera camera, Object object);


	//ゲッター

	Matrix4x4 GetViewPortMatrix() { return viewportMatrix; }

};

