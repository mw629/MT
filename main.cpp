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

	AABB aabb = { {-0.5f,-0.5f,-0.5f} ,{0.5f,0.5f,0.5f} };
	Segment segment = { {-0.7f,0.3f,0.0f},{2.0f,-0.5f,0.0f} };

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
		ImGui::DragFloat3("cameraTranslate", &camera.pos.x, 0.01f);
		ImGui::DragFloat3("cameraRotate", &camera.rotate.x, 0.01f);

		ImGui::DragFloat3("aabb", &aabb.min.x, 0.01f);
		ImGui::DragFloat3("aabb", &aabb.max.x, 0.01f);
		ImGuiLine(segment);

		ImGui::End();





		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		draw->DrawGrid(camera);
		if (IsCollision(aabb, segment)) {
			draw->DrawAABB(aabb, camera, RED);
		}
		else {
			draw->DrawAABB(aabb, camera, WHITE);
		}
		draw->DrawLine(segment, camera, WHITE);


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
