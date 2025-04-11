#include <Novice.h>
#include "Calculation.h"


const char kWindowTitle[] = "LC1A_27_ワタナベ_マサト";

static const int kColumnWidth = 60;
void VectorScreenPrintf(int x, int y, const Vecto3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };


	Vecto3 v1 = {1.0f,3.0f,-5.0f};
	Vecto3 v2 = { 4.0f,-1.0f,2.0f };
	float k = 4.0f;

	Vecto3 add;
	Vecto3 subtract;
	Vecto3 multiply;
	float dot;
	float length;
	Vecto3 normalize;

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
		
		add = AddVecto3(v1, v2);
		subtract = SubtractVector3(v1, v2);
		multiply = ScalarMultiply(v1, k);
		dot = Dot(v1, v2);
		length = Lengeh(v1);
		normalize = Normalize(v2);


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		VectorScreenPrintf(0, 0, add, ":Add");
		VectorScreenPrintf(0, 20, subtract, ":Subtrat");
		VectorScreenPrintf(0, 40, multiply, ":Multiply");
		Novice::ScreenPrintf(0, 60, "%.02f :Dot", dot);
		Novice::ScreenPrintf(0, 80, "%.02f :Length", length);
		VectorScreenPrintf(0, 100, normalize, ":normalize");

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
