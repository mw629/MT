#include <Novice.h>
#include "Calculation.h"

static const int kRowHeight = 20;
static const int kColimnWidth = 80;
static const int kWindowWidth = 1280;
static const int kWindowHight = 720;

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



	Vector3 cameraPos = { 1.0f,1.0f,1.0f };
	Vector3 cameraRotate = { 0.0f,0.0f,0.0f };
	Vector3 cameraScale = { 1.0f,1.0f,1.0f };

	Vector3 pos = { 1.0f,1.0f,1.0f };
	Vector3 rotate = { 0.0f,0.0f,0.0f };
	Vector3 scale = { 1.0f,1.0f,1.0f };


	Matrix4x4 worldMatrix;
	Matrix4x4 cameraMatrix;
	Matrix4x4 viewMatrix;
	Matrix4x4 projectionMatrix;
	Matrix4x4 worldViewProjectiveMatrix;
	Matrix4x4 viewportMatrix;
	Vector3 screenVertices[3];

	Vector3 ndcVertex;

	Vector3 kLocalVertices[3] = {
		{0.0f,5.0f,1.0f},
		{-5.0f,-5.0f,1.0f},
		{5.0f,-5.0f,1.0f}
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

		worldMatrix = MakeAffineMatrix(pos, scale, rotate);
		cameraMatrix = MakeAffineMatrix(cameraPos, cameraScale, cameraRotate);
		viewMatrix = InverseMatrix4x4(cameraMatrix);
		projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHight), 0.1f, 100.0f);
		worldViewProjectiveMatrix = MultiplyMatrix4x4(worldMatrix, MultiplyMatrix4x4(viewMatrix, projectionMatrix));
		viewportMatrix = MakeViewPortMatrix(1.0f, 1.0f, 640, 360, 0.0f, 1.0f);
		for (int i = 0; i < 3; ++i) {
			ndcVertex = Transform(kLocalVertices[i], worldViewProjectiveMatrix);
			screenVertices[i] = Transform(ndcVertex, viewportMatrix);
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
		
		VectorScreenPrintf(0, 0, cross, ":Cross");
	 
		for (int i = 0; i < 3; i++) {
			VectorScreenPrintf(0, 20 + 20 * i, screenVertices[i], "");
		}



		
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
