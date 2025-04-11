#include <Novice.h>
#include "Calculation.h"

static const int kRowHeight = 20;
static const int kColimnWidth = 60;

void VectorScreenPrintf(int x, int y, const Vecto3& vector, const char* label) {
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

const char kWindowTitle[] = "LC1A_27_ワタナベ_マサト";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };


	
	Vecto3 cameraPos = { 0.0f, 0.0f, 0.0f};
	Matrix4x4 cameraMatrix;

	Matrix4x4 viewMatrix;
	Matrix4x4 projectionMatrix;
	Matrix4x4 worldViewProjectionMatrix;
	Matrix4x4 viewportMatrix;

	Vecto3 pos = { 0.0f,0.0f,0.0f };//1.0f,-400.0f,100.0f
	Vecto3 kLocalVertices[3] =
	{
		{10.0f,10.0f,0.0f},
		{30.0f,10.0f,0.0f},
		{20.0f,30.0f,0.0f}
	};
	Matrix4x4 WorldMatrix;

	// 垂直方向視野角
	float fovAngleY = 90.0f;
	// ビューポートのアスペクト比
	float aspectRatio = (float)720 / 1280;
	// 深度限界（手前側）
	float nearZ = 0.1f;
	// 深度限界（奥側）
	float farZ = 1.0f;



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
		


		WorldMatrix = MakeAffineMatrix(pos, { 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f });
		cameraMatrix = MakeAffineMatrix(cameraPos, { 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f });

		viewMatrix = InverseMatrix4x4(cameraMatrix);
		projectionMatrix = MakePerspectiveFovMatrix(fovAngleY, aspectRatio, nearZ, farZ);

		worldViewProjectionMatrix = MultiplyMatrix4x4(WorldMatrix, MultiplyMatrix4x4(viewMatrix, projectionMatrix));

		viewportMatrix = MakeViewPortMatrix(1280.0f, 720.0f, 0.0f, 0.0f, 0.0f, 1.0f);

		Vecto3 screenVertice[3];

		for (int i = 0; i < 3; i++) {
			Vecto3 ndcVertice = Transform(kLocalVertices[i], worldViewProjectionMatrix);
			screenVertice[i] = Transform(ndcVertice, viewportMatrix);
		}



		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawTriangle(
			static_cast<int>(screenVertice[0].x), static_cast<int>(screenVertice[0].y),
			static_cast<int>(screenVertice[1].x), static_cast<int>(screenVertice[1].y),
			static_cast<int>(screenVertice[2].x), static_cast<int>(screenVertice[2].y),
			0xFFFFFFFF, kFillModeSolid);

		for (int i = 0; i < 3; i++)
		{
			Novice::ScreenPrintf(10, 10 + i * 20, "screenVertice[%d] = (%f, %f)", i, screenVertice[i].x, screenVertice[i].y);
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
