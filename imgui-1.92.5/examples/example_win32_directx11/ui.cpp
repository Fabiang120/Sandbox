#include "ui.h"
#include "imgui.h"

void RenderUI(UIState& state){
    ImGui::SetNextWindowSize(ImVec2(600, 400));
    ImGui::Begin("My New IMGUI App", &state.Open, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
    ImGui::SetCursorPosX(ImGui::GetWindowSize().x / 2 - ImGui::CalcTextSize("Welcome to my new ImGui app").x / 2);
    ImGui::Text("Welcome to my new ImGui app");
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.6f, 1.0f, 1.0f));
    if (ImGui::Button("Click Me")) {

    }
    ImGui::PopStyleColor();
    ImGui::SameLine();
    ImGui::Checkbox("Magic Text", &state.CheckBoxValue);
    ImGui::SliderFloat("Float Slider", &state.Starting, 0.0f, 100.0f);
    ImGui::SliderInt("Int Slider", &state.Starting1, 0, 100);
    ImGui::InputText("Name", state.TextChars, sizeof(state.TextChars));
    ImDrawList* draw = ImGui::GetWindowDrawList();
    ImVec2 p = ImGui::GetCursorScreenPos();
    draw->AddRectFilled(
        p,
        ImVec2(p.x + 200, p.y + 100),
        IM_COL32(255, 0, 0, 255),
        6.0f
    );
    ImGui::Dummy(ImVec2(200, 100));
    ImGui::End();
}
