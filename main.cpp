#include <Novice.h>
#include <stdint.h>
#include <cmath>
#include <imgui.h>

#include "Calculation.h"

#define M_PI 3.14f


const char kWindowTitle[] = "LC1A_27_ワタナベ_マサト";

struct Sphere {
	Vector3 center;//中心
	float radius;//半径
};

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
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
			Matrix4x4 worldViewProjectiveMatrix = MultiplyMatrix4x4(worldMatrix, viewProjectionMatrix);

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

void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
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
		worldViewProjectiveMatrix = MultiplyMatrix4x4(worldMatrix, viewProjectionMatrix);
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
		worldViewProjectiveMatrix = MultiplyMatrix4x4(worldMatrix, viewProjectionMatrix);
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



// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Vector3 v1{ 1.2f,-3.9f,2.5f };
	Vector3 v2{ 2.8f,0.4f,-1.3f };
	Vector3 cross = Cross(v1, v2);

	Sphere sphere = { {0.0f,0.0f,0.0f},{1.0f} };

	Vector3 cameraPos = { 0.0f,1.9f,-6.49f };
	Vector3 cameraRotate = { 0.26f,0.0f,0.0f };
	Vector3 cameraScale = { 1.0f,1.0f,1.0f };

	Vector3 pos = { 0.0f,0.0f,0.0f };
	Vector3 rotate = { 0.0f,0.0f,0.0f };
	Vector3 scale = { 1.0f,1.0f,1.0f };


	Matrix4x4 worldMatrix;
	Matrix4x4 cameraMatrix;
	Matrix4x4 viewMatrix;
	Matrix4x4 projectionMatrix;
	Matrix4x4 worldViewProjectiveMatrix;
	Matrix4x4 viewportMatrix;
	Vector3 screenVertices[3];

	Vector3 ndcVertex[3];

	Vector3 kLocalVertices[3] = {
		{0.0f,1.0f,0.0f},
		{-1.0f,-1.0f,0.0f},
		{1.0f,-1.0f,0.0f}
	};
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		ImGui::Begin("window");
		ImGui::DragFloat3("cameraTranslate", &cameraPos.x, 0.01f);
		ImGui::DragFloat3("cameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("cameraCenter", &sphere.center.x, 0.01f);
		ImGui::DragFloat("sphereRadius", &sphere.radius, 0.01f);
		ImGui::End();


		rotate.y += 0.1f;

		if (keys[DIK_W]) {
			pos.z += 0.1f;
		}
		if (keys[DIK_S]) {
			pos.z -= 0.1f;
		}

		if (keys[DIK_A]) {
			pos.x -= 0.1f;
		}
		if (keys[DIK_D]) {
			pos.x += 0.1f;
		}


		worldMatrix = MakeAffineMatrix(pos, scale, rotate);
		cameraMatrix = MakeAffineMatrix(cameraPos, cameraScale, cameraRotate);
		viewMatrix = InverseMatrix4x4(cameraMatrix);
		projectionMatrix = MakePerspectiveFovMatrix(0.45f, 1280.0f / 720.0f, 0.1f, 100.0f);
		worldViewProjectiveMatrix = MultiplyMatrix4x4(worldMatrix, MultiplyMatrix4x4(viewMatrix, projectionMatrix));
		viewportMatrix = MakeViewPortMatrix(1280.0f, 720.0f, 0.0f, 0.0f, 0.0f, 1.0f);
		for (int i = 0; i < 3; ++i) {
			ndcVertex[i] = Transform(kLocalVertices[i], worldViewProjectiveMatrix);
			screenVertices[i] = Transform(ndcVertex[i], viewportMatrix);
		}


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(MultiplyMatrix4x4(viewMatrix, projectionMatrix), viewportMatrix);
		DrawSphere(sphere, MultiplyMatrix4x4(viewMatrix, projectionMatrix), viewportMatrix, BLACK);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
