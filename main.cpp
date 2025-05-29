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

bool IsCollision(const Triangle& triangle, const Segment& line) {

	Vector3 cross01 = Cross(SubtractVector3(triangle.vertices[0], triangle.vertices[1]), ClosestPoint(triangle.vertices[1], line));
	Vector3 cross02 = Cross(SubtractVector3(triangle.vertices[1], triangle.vertices[2]), ClosestPoint(triangle.vertices[2], line));
	Vector3 cross03 = Cross(SubtractVector3(triangle.vertices[2], triangle.vertices[0]), ClosestPoint(triangle.vertices[0], line));
	
	
	Vector3 edge1 = triangle.vertices[1] - triangle.vertices[0];
	Vector3 edge2 = triangle.vertices[2] - triangle.vertices[0];

	Vector3 normal = Cross(edge1, edge2);

	if (Dot(cross01, normal) >= 0.0f &&
		Dot(cross02, normal) >= 0.0f &&
		Dot(cross03, normal) >= 0.0f) {
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

	Triangle triangle = { Vector3{-1.0f,0.0f,0.0f},Vector3{0.0f,1.0f,0.0f }, Vector3{ 1.0f,0.0f,0.0f } };
	Segment line = { {-1,-1,0}, {1,1,0} };

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

		ImGui::DragFloat3("line", &line.origin.x, 0.01f);
		ImGui::DragFloat3("line", &line.diff.x, 0.01f);
		ImGui::DragFloat3("line.origin", &line.origin.x, 0.01f);
		ImGui::DragFloat3("line.diff", &line.diff.x, 0.01f);

		ImGui::DragFloat3("triangle[0]", &triangle.vertices[0].x, 0.01f);
		ImGui::DragFloat3("triangle[1]", &triangle.vertices[1].x, 0.01f);
		ImGui::DragFloat3("triangle[2]", &triangle.vertices[2].x, 0.01f);
		ImGui::End();





		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		draw->DrawGrid(camera);
		if (IsCollision(triangle, line)) {
			draw->DrawLine(line, camera, RED);
		}
		else {
			draw->DrawLine(line, camera, BLACK);
		}
		draw->DrawTriangle(triangle, camera, BLACK,kFillModeWireFrame);

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
