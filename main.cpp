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

	Object point[3] = {
		{{0.2f,1.0f,0.0f},
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,-6.8f},},
		{{0.4f,0.0f,0.0f},
		{0.0f,0.0f,-1.4f},
		{0.0f,0.0f,0.0f},},
		{{0.3f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
		{1.0f,1.0f,1.0f},},
	};

	Matrix4x4 worldMatrix;
	Matrix4x4 projectionMatrix;
	Matrix4x4 worldViewProjectiveMatrix[3];
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
		ImGuiCamera(camera);
		if (ImGui::CollapsingHeader("point1")) {
			ImGui::DragFloat3("Shoulder.pos", &point[0].pos.x, 0.01f);
			ImGui::DragFloat3("Elbow.rotate", &point[0].rotate.x, 0.01f);
			ImGui::DragFloat3("Hand.scale", &point[0].scale.x, 0.01f);
		}
		if (ImGui::CollapsingHeader("point1")) {
			ImGui::DragFloat3("Shoulder.pos", &point[1].pos.x, 0.01f);
			ImGui::DragFloat3("Elbow.rotate", &point[1].rotate.x, 0.01f);
			ImGui::DragFloat3("Hand.scale", &point[1].scale.x, 0.01f);
		}
		if (ImGui::CollapsingHeader("point3")) {
			ImGui::DragFloat3("Shoulder.pos", &point[2].pos.x, 0.01f);
			ImGui::DragFloat3("Elbow.rotate", &point[2].rotate.x, 0.01f);
			ImGui::DragFloat3("Hand.scale", &point[2].scale.x, 0.01f);
		}
		ImGui::DragFloat3("pos1", &drawPos[0].x, 0.01f);
		ImGui::DragFloat3("pos2", &drawPos[1].x, 0.01f);
		ImGui::DragFloat3("pos3", &drawPos[2].x, 0.01f);

		ImGui::End();
		draw->DrawGrid(camera);

		worldMatrix= MakeAffineMatrix(point[0].pos, point[0].scale, point[0].rotate);
		projectionMatrix = draw->MakeprojectionMatrix(camera);

		worldViewProjectiveMatrix[0] = Multiply(worldMatrix, draw->MakeprojectionMatrix(camera));

		drawPos[0] = Transform(Vector3(0, 0, 0), Multiply(worldViewProjectiveMatrix,draw->GetViewPortMatrix()));
		drawPos[0] = Transform(Vector3(0, 0, 0), Multiply(worldViewProjectiveMatrix, draw->GetViewPortMatrix()));


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawLine(static_cast<int>(drawPos[0].x), static_cast<int>(drawPos[0].y), static_cast<int>(drawPos[1].x), static_cast<int>(drawPos[1].y), BLACK);
		Novice::DrawLine(static_cast<int>(drawPos[1].x), static_cast<int>(drawPos[1].y), static_cast<int>(drawPos[2].x), static_cast<int>(drawPos[2].y), BLACK);

		for (int i = 0; i < 3; i++) {
			Novice::DrawEllipse(static_cast<int>(drawPos[i].x), static_cast<int>(drawPos[i].y), 3, 3, 0.0f, 255 + 255 * i, kFillModeSolid);
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

	delete draw;


	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
