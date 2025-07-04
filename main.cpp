#include <Novice.h>
#include <stdint.h>
#include <cmath>
#include <imgui.h>

#include "Calculation.h"
#include "Draw.h"
#include "Collision.h"
#include <algorithm>
#include "ImGuiDraw.h"

#define M_PI 3.14f


const char kWindowTitle[] = "LC1A_27_ワタナベ_マサト";




// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };


	Draw* draw = new Draw();

	Camera camera;
	camera.pos = { 0.0f,1.9f,-6.49f };
	camera.scale = { 1.0f,1.0f,1.0f };
	camera.rotate = { 0.26f,0.0f,0.0f };

	Vector3 drawPos[2];
	Matrix4x4 affine[2];

	Pundulm pundulm;
	pundulm.anchor = { 0.0f,1.0f,0.0f };
	pundulm.lengrh = 0.8f;
	pundulm.angle = 0.7f;
	pundulm.angularVelocity = 0.0f;
	pundulm.angularAcceleration = 0.0f;

	Sphere sphere;
	sphere.radius = 0.1f;

	bool isMove = false;
	

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
		ImGui::Checkbox("move", &isMove);
		
		ImGui::End();

		PendulumMove(pundulm, sphere, isMove);

		
		

		affine[0] = MakeAffineMatrix(pundulm.anchor, { 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f });
		drawPos[0] = draw->Renderingpipeline(camera, affine[0]);
		affine[1] = MakeAffineMatrix(sphere.center, { 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f });
		drawPos[1] = draw->Renderingpipeline(camera, affine[1]);


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		draw->DrawGrid(camera);

		Novice::DrawLine(int(drawPos[0].x), int(drawPos[0].y), int(drawPos[1].x), int(drawPos[1].y), WHITE);
		draw->DrawSphere(sphere, camera, WHITE);

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

	delete draw;


	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
