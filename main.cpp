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

	Plane plane;
	plane.normal = Normalize({ -0.2f, 0.9f,-0.3f });
	plane.distance = 0.0f;

	Ball ball{};
	ball.shape.center = { 0.0f,1.2f,0.3f };
	ball.mass = 2.0f;
	ball.shape.radius = 0.05f;
	ball.color = WHITE;
	ball.acceleration = { 0.0f,-9.8f,0.0f };

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
		ImGui::DragFloat3("pos", &camera.pos.x, 0.1f, 1.0f);
		ImGui::DragFloat3("angle", &camera.rotate.x, 0.1f, 1.0f);
		ImGui::End();

		if (keys[DIK_SPACE]) {
			isMove = true;
		}

		if (isMove) {
		BallMove(ball, plane, 0.9f);
		}
			


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		draw->DrawGrid(camera);

		draw->DrawPlane(plane,camera,WHITE);
		draw->DrawSphere(ball.shape, camera, ball.color);


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
