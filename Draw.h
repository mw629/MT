#include "Calculation.h"
#include "Structure.h"



#pragma once
class Draw
{
private:

	float width=0.0f;
	float height=0.0f;
	float left=0.0f;
	float top=0.0f;
	float minD=0.0f;
	float maxD=0.0f;


	Matrix4x4 cameraMatrix;
	Matrix4x4 viewMatrix;
	Matrix4x4 projectionMatrix;
	Matrix4x4 worldViewProjectiveMatrix;
	Matrix4x4 viewportMatrix = MakeViewPortMatrix(width, height, left, top, minD, maxD);



public:

	void DrawSphere(const Sphere& sphere, Camera camera,uint32_t color);

	void DrawGrid(Camera camera);

	Matrix4x4 MakeprojectionMatrix(Camera camera);

	Matrix4x4 Renderingpipeline(Camera camera, Object object);

};

