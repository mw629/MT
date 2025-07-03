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

	Vector3 translate[3] = {
		{0.2f,1.0f,0.0f},
		{0.4f,0.0f,0.0f},
		{0.3f,0.0f,0.0f}
	};
	Vector3 rorares[3] = {
		{0.0f,0.0f,-6.8f},
		{0.0f,0.0f,-1.4f},
		{0.0f,0.0f,0.0f}
	};
	Vector3 scales[3] = {
		{1.0f,1.0f,1.0f},
		{1.0f,1.0f,1.0f},
		{1.0f,1.0f,1.0f}
	};


	Matrix4x4 affine[3];

	Vector3 drawPos[3];

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

		if (ImGui::CollapsingHeader("Shoulder")) {
			ImGui::SliderFloat4("Stranslate", &translate[0].x, -10.0f, 10.0f);
			ImGui::SliderFloat4("Srorares", &rorares[0].x, -10.0f, 10.0f);
			ImGui::SliderFloat4("Sscales", &scales[0].x, -10.0f, 10.0f);
		}
		if (ImGui::CollapsingHeader("Elbow")) {
			ImGui::SliderFloat4("Etranslate", &translate[1].x, -10.0f, 10.0f);
			ImGui::SliderFloat4("Erorares", &rorares[1].x, -10.0f, 10.0f);
			ImGui::SliderFloat4("Escales", &scales[1].x, -10.0f, 10.0f);
		}

		if (ImGui::CollapsingHeader("Hand")) {
			ImGui::SliderFloat4("HStranslate", &translate[2].x, -10.0f, 10.0f);
			ImGui::SliderFloat4("Hrorares", &rorares[2].x, -10.0f, 10.0f);
			ImGui::SliderFloat4("Hscales", &scales[2].x, -10.0f, 10.0f);
		}

		if (ImGui::CollapsingHeader("pos")) {
			ImGui::SliderFloat4("Spos", &drawPos[0].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("Epos", &drawPos[1].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("Hpos", &drawPos[2].x, 0.0f, 1.0f);
		}

		ImGui::End();


		affine[0] = MakeAffineMatrix(translate[0], scales[0], rorares[0]);
		drawPos[0] = draw->Renderingpipeline(camera, affine[0]);
		affine[1]= MakeAffineMatrix(translate[1], scales[1], rorares[1]);
		affine[1] = Multiply(affine[1], affine[0]);
		drawPos[1] = draw->Renderingpipeline(camera, affine[1]);
		affine[2] = MakeAffineMatrix(translate[2], scales[2], rorares[2]);
		affine[2] = Multiply(affine[2], affine[1]);
		drawPos[2] = draw->Renderingpipeline(camera, affine[2]);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		draw->DrawGrid(camera);

		Novice::DrawLine(static_cast<int>(drawPos[0].x), static_cast<int>(drawPos[0].y), static_cast<int>(drawPos[1].x), static_cast<int>(drawPos[1].y), BLACK);
		Novice::DrawLine(static_cast<int>(drawPos[1].x), static_cast<int>(drawPos[1].y), static_cast<int>(drawPos[2].x), static_cast<int>(drawPos[2].y), BLACK);


		Novice::DrawEllipse(static_cast<int>(drawPos[0].x), static_cast<int>(drawPos[0].y), 5, 5, 0.0f, RED, kFillModeSolid);
		Novice::DrawEllipse(static_cast<int>(drawPos[1].x), static_cast<int>(drawPos[1].y), 5, 5, 0.0f, GREEN, kFillModeSolid);
		Novice::DrawEllipse(static_cast<int>(drawPos[2].x), static_cast<int>(drawPos[2].y), 5, 5, 0.0f, BLUE, kFillModeSolid);


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
