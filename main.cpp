#include <Novice.h>
#include "Calculation.h"

const char kWindowTitle[] = "LC1A_27_ワタナベ_マサト";

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
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };


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

		Vecto3 translate{ 4.1f,2.6f,0.8f };
		Vecto3 scale{ 1.5f,5.2f,7.3f };
		Matrix4x4 translateMatrix = Translation(translate);
		Matrix4x4 scaleMatrix = Scale(scale);
		Vecto3 point{ 2.3f,3.8f,1.4f };
		Matrix4x4 transformMatrix = {
			1.0f,2.0f,3.0f,4.0f,
			3.0f,1.0f,1.0f,2.0f,
			1.0f,4.0f,2.0f,3.0f,
			2.0f,2.0f,1.0f,3.0f, };
		Vecto3 tranformed = Transform(point, transformMatrix);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		VectorScreenPrintf(0, 0, tranformed, "transFromed");
		MatrixScreenPrintf(0, kRowHeight, translateMatrix, "translateMatrix");
		MatrixScreenPrintf(0, kRowHeight * 6, scaleMatrix, "scaleMatrix");

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
