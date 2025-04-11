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
	


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
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
