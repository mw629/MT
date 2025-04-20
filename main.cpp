#include <Novice.h>
#include "Calculation.h"


const char kWindowTitle[] = "LC1A_27_ワタナベ_マサト";

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



	Vector3 cameraPos = { 0.0f,0.0f,-10.0f };
	Vector3 cameraRotate = { 0.0f,0.0f,0.0f };
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
		projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHight), 0.1f, 100.0f);
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

		Novice::DrawTriangle(static_cast<int>(screenVertices[0].x), static_cast<int>(screenVertices[0].y),
			static_cast<int>(screenVertices[1].x), static_cast<int>(screenVertices[1].y),
			static_cast<int>(screenVertices[2].x), static_cast<int>(screenVertices[2].y),
			RED, kFillModeSolid);

		VectorScreenPrintf(10, 0, cross, ":Cross");




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
