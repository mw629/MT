#include <Novice.h>
#include <stdint.h>
#include <cmath>

#include "Draw.h"

#define M_PI 3.14f

void Draw::DrawSphere(const Sphere& sphere, Camera camera, uint32_t color) {
	const uint32_t kSubdivision = 10;
	const float kLonEvery = M_PI * 2.0f / kSubdivision;
	const float kLatEvery = M_PI / kSubdivision;
	//緯度の方向に分割 -n/2 ~ n/2
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -M_PI / 2.0f + kLatEvery * latIndex;//現在の緯度
		//軽度の方向に分割
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery;//現在の経度
			Vector3 a, b, c;
			Vector3 VertexA, VertexB, VertexC;
			Vector3 screenPosA, screenPosB, screenPosC;


			a = { std::cos(lat) * std::cos(lon),
				std::sin(lat),
				std::cos(lat) * std::sin(lon) };

			b = { std::cos(lat + kLatEvery) * std::cos(lon),
				std::sin(lat + kLatEvery),
				std::cos(lat + kLatEvery) * std::sin(lon) };

			c = { std::cos(lat) * std::cos(lon + kLonEvery),
				std::sin(lat),
				std::cos(lat) * std::sin(lon + kLonEvery) };


			Matrix4x4 worldMatrix = MakeAffineMatrix(sphere.center, { 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f });
			Matrix4x4 worldViewProjectiveMatrix = MultiplyMatrix4x4(worldMatrix, MakeprojectionMatrix(camera));

			VertexA = Transform(a * sphere.radius, worldViewProjectiveMatrix);
			VertexB = Transform(b * sphere.radius, worldViewProjectiveMatrix);
			VertexC = Transform(c * sphere.radius, worldViewProjectiveMatrix);

			screenPosA = Transform(VertexA, viewportMatrix);
			screenPosB = Transform(VertexB, viewportMatrix);
			screenPosC = Transform(VertexC, viewportMatrix);

			Novice::DrawLine(static_cast<int>(screenPosA.x), static_cast<int>(screenPosA.y), static_cast<int>(screenPosB.x), static_cast<int>(screenPosB.y), color);
			Novice::DrawLine(static_cast<int>(screenPosA.x), static_cast<int>(screenPosA.y), static_cast<int>(screenPosC.x), static_cast<int>(screenPosC.y), color);
		}
	}

}


void Draw::DrawGrid(Camera camera)
{

	const float kGridHalfWidth = 2.0f;//Gridの半分の幅
	const uint32_t kSubdivision = 10;//分割数
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision);//1つ分の長さ

	Matrix4x4 worldViewProjectiveMatrix;
	Matrix4x4 worldMatrix;

	Vector3 pos;
	Vector3 startVertex;
	Vector3 endVertex;
	Vector3 screenStartPos;
	Vector3 screenEndPos;

	//奥から手前への線を順々に引いていく
	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {
		pos = { 0.0f ,0.0f,2.0f - kGridEvery * xIndex };
		worldMatrix = MakeAffineMatrix(pos, { 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f });
		worldViewProjectiveMatrix = MultiplyMatrix4x4(worldMatrix, MakeprojectionMatrix(camera));
		startVertex = Transform({ -2.0f,0.0f,0.0f }, worldViewProjectiveMatrix);
		endVertex = Transform({ 2.0f,0.0f,0.0f }, worldViewProjectiveMatrix);
		screenStartPos = Transform(startVertex, viewportMatrix);
		screenEndPos = Transform(endVertex, viewportMatrix);;
		if (xIndex == kSubdivision / 2) {
			Novice::DrawLine(static_cast<int>(screenStartPos.x), static_cast<int>(screenStartPos.y), static_cast<int>(screenEndPos.x), static_cast<int>(screenEndPos.y), 0x000000FF);
		}
		else {
			Novice::DrawLine(static_cast<int>(screenStartPos.x), static_cast<int>(screenStartPos.y), static_cast<int>(screenEndPos.x), static_cast<int>(screenEndPos.y), 0xAAAAAAFF);
		}
	}
	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {
		pos = { 2.0f - kGridEvery * zIndex ,0.0f,0.0f };
		worldMatrix = MakeAffineMatrix(pos, { 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f });
		worldViewProjectiveMatrix = MultiplyMatrix4x4(worldMatrix, MakeprojectionMatrix(camera));
		startVertex = Transform({ 0.0f,0.0f,-2.0f }, worldViewProjectiveMatrix);
		endVertex = Transform({ 0.0f,0.0f,2.0f }, worldViewProjectiveMatrix);
		screenStartPos = Transform(startVertex, viewportMatrix);
		screenEndPos = Transform(endVertex, viewportMatrix);;
		if (zIndex == kSubdivision / 2) {
			Novice::DrawLine(static_cast<int>(screenStartPos.x), static_cast<int>(screenStartPos.y), static_cast<int>(screenEndPos.x), static_cast<int>(screenEndPos.y), 0x000000FF);
		}
		else {
			Novice::DrawLine(static_cast<int>(screenStartPos.x), static_cast<int>(screenStartPos.y), static_cast<int>(screenEndPos.x), static_cast<int>(screenEndPos.y), 0xAAAAAAFF);
		}
	}
}

void Draw::DrawPlane(const Plane& plane, Camera camera, uint32_t color)
{
	Vector3 center = ScalarMultiply(plane.normal, plane.distance);
	Vector3 Perpendiculars[4];
	Perpendiculars[0] = Normalize(Perpendicular(plane.normal));
	Perpendiculars[1] = { -Perpendiculars[0].x,-Perpendiculars[0].y,-Perpendiculars[0].z };
	Perpendiculars[2] = Cross(plane.normal, Perpendiculars[0]);
	Perpendiculars[3] = { -Perpendiculars[2].x,-Perpendiculars[2].y,-Perpendiculars[2].z };

	Vector3 points[4];
	for (int32_t index = 0; index < 4; ++index) {
		Vector3 extend = ScalarMultiply(Perpendiculars[index], 2.0f);
		Vector3 point = AddVector3(center, extend);
		points[index] = Transform(Transform(point, MakeprojectionMatrix(camera)), viewportMatrix);
	}

	Novice::DrawLine(static_cast<int>(points[0].x), static_cast<int>(points[0].y), static_cast<int>(points[2].x), static_cast<int>(points[2].y), color);
	Novice::DrawLine(static_cast<int>(points[0].x), static_cast<int>(points[0].y), static_cast<int>(points[3].x), static_cast<int>(points[3].y), color);
	Novice::DrawLine(static_cast<int>(points[1].x), static_cast<int>(points[1].y), static_cast<int>(points[2].x), static_cast<int>(points[2].y), color);
	Novice::DrawLine(static_cast<int>(points[1].x), static_cast<int>(points[1].y), static_cast<int>(points[3].x), static_cast<int>(points[3].y), color);

}

Matrix4x4 Draw::MakeprojectionMatrix(Camera camera)
{
	cameraMatrix = MakeAffineMatrix(camera.pos, camera.scale, camera.rotate);
	viewMatrix = InverseMatrix4x4(cameraMatrix);
	projectionMatrix = MakePerspectiveFovMatrix(0.45f, 1280.0f / 720.0f, 0.1f, 100.0f);

	return MultiplyMatrix4x4(viewMatrix, projectionMatrix);
}

Matrix4x4 Draw::Renderingpipeline(Camera camera, Object object)
{
	Matrix4x4 worldMatrix = MakeAffineMatrix(object.pos, object.scale, object.rotate);
	Matrix4x4 worldViewProjectiveMatrix = MultiplyMatrix4x4(worldMatrix, MakeprojectionMatrix(camera));
	return worldViewProjectiveMatrix;
}
