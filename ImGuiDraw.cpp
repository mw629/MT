#include "ImGuiDraw.h"
#include <imgui.h>

void ImGuiCamera(Camera& camera)
{
	if (ImGui::CollapsingHeader("Camera")) {
		ImGui::DragFloat3("Camera.pos", &camera.pos.x, 0.01f);
		ImGui::DragFloat3("Camera.rotate", &camera.rotate.x, 0.01f);
		ImGui::DragFloat3("Camera.scale", &camera.scale.x, 0.01f);
	}
}

void ImGuiLine(Segment& segment)
{
	if (ImGui::CollapsingHeader("Segment")) {
		ImGui::DragFloat3("Segment", &segment.origin.x, 0.01f);
		ImGui::DragFloat3("Segment.diff", &segment.diff.x, 0.01f);
	}
}

void ImGuiBezierCurve(BezierCurve& bezierCurve)
{
	if (ImGui::CollapsingHeader("BezierCurve")) {
		ImGui::DragFloat3("bezierCurve.start", &bezierCurve.start.x, 0.01f);
		ImGui::DragFloat3("bezierCurve.controlPoint", &bezierCurve.controlPoint.x, 0.01f);
		ImGui::DragFloat3("bezierCurve.end", &bezierCurve.end.x, 0.01f);
	}
}
