#include <Novice.h>
#include <stdint.h>
#include <cmath>
#include <imgui.h>

#include "Calculation.h"
#include "Draw.h"

#define M_PI 3.14f


const char kWindowTitle[] = "LC1A_27_ワタナベ_マサト";


bool IsCollision(const Sphere& sphere1, const Sphere& sphere2) {
	
	float distance = Lengeh(sphere2.center - sphere1.center);

	if (distance <= sphere1.radius + sphere2.radius) {
		return true;
	}
	return false;
}

bool IsCollision(const Sphere& sphere, const Plane& plane) {
	
	float distance = AbsValue(Dot(plane.normal, sphere.center) - plane.distance);
	if (distance <= sphere.radius) {
		return true;
	}
	return false;
}

bool IsCollision(const Plane& plane, const Segment& line) {
	float dot = Dot(plane.normal, line.diff);

	if (dot == 0.0f) { return false; }

	float t = (plane.distance - Dot(line.origin, plane.normal)) / dot;

	if (0.0f <= t && t <= 1.0f) {
		return true;
	}
	return false;

}

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

	Segment line = { {0,0,0}, {0,0,0} };
	Plane plane = { {0.0f,1.0f,0.0f},1.0f };

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
	

		ImGui::DragFloat3("line.origin", &line.origin.x, 0.01f);
		ImGui::DragFloat3("line.diff", &line.diff.x, 0.01f);

		ImGui::DragFloat3("Plane.Normal", &plane.normal.x, 0.01f);
		ImGui::DragFloat("Planedistance", &plane.distance,0.01f);
		ImGui::End();
		plane.normal = Normalize(plane.normal);

	



		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		draw->DrawGrid(camera);
		if (IsCollision(plane,line)) {
			draw->DrawLine(line, camera, RED);
		}
		else {
			draw->DrawLine(line, camera, BLACK);
		}
		draw->DrawPlane(plane, camera, BLACK);
	
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
