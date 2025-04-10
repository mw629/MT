#include <Novice.h>
#include "Calculation.h"

static const int kRowHeight = 20;
static const int kColimnWidth = 60;
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
	Novice::ScreenPrintf(x, y, "%s", label);
	for (int row = 1; row < 5; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(
				x + column * kColimnWidth, y + row * kRowHeight, "%6.02f", matrix.m[row-1][column]);
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

	Matrix4x4 m1 = {
		3.2f,0.7f,9.6f,4.4f,
		5.5f,1.3f,7.8f,2.1f,
		6.9f,8.0f,2.6f,1.0f,
		0.5f,7.2f,5.1f,3.3f };

	Matrix4x4 m2 = {
		4.1f,6.5f,3.3f,2.2f,
		8.8f,0.6f,9.9f,7.7f,
		1.1f,5.5f,6.6f,0.0f,
		3.3f,9.9f,8.8f,2.2f };



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

		Matrix4x4 add = AddMatrix4x4(m1, m2);
		Matrix4x4 multiply = MultiplyMatrix4x4(m1, m2);
		Matrix4x4 subtract = SubtractMatrix(m1, m2);
		Matrix4x4 inverseM1 = InverseMatrix4x4(m1);
		Matrix4x4 inverseM2 = InverseMatrix4x4(m2);
		Matrix4x4 transposeM1 = TransposeMatrix4x4(m1);
		Matrix4x4 transposeM2 = TransposeMatrix4x4(m2);
		Matrix4x4 identity = IdentityMatrix();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		MatrixScreenPrintf(0, 0, add, "Add");
		MatrixScreenPrintf(0, kRowHeight * 6, subtract, "Subtract");
		MatrixScreenPrintf(0, kRowHeight * 6 * 2, multiply, "Multiply");
		MatrixScreenPrintf(0, kRowHeight * 6 * 3, inverseM1, "inverseM1");
		MatrixScreenPrintf(0, kRowHeight * 6 * 4, inverseM2, "inverseM2");
		MatrixScreenPrintf(kColimnWidth * 5, 0, transposeM1, "transposeM1");
		MatrixScreenPrintf(kColimnWidth * 5, kRowHeight * 6, transposeM2, "transposeM2");
		MatrixScreenPrintf(kColimnWidth * 5, kRowHeight * 6 * 2, identity, "identity");


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
