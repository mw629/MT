#include "ImGuiDraw.h"
#include <imgui.h>

void ImGuiLine(Segment &segment)
{
	ImGui::DragFloat3("Segment", &segment.origin.x, 0.01f);
	ImGui::DragFloat3("Segment.diff", &segment.diff.x, 0.01f);
}
