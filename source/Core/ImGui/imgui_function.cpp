#include "Core/ImGui/imgui_function.h"

void Menu::barMenu() {

    if (ImGui::BeginMainMenuBar()) {

        if (ImGui::BeginMenu("File"))
        {
            
            if (ImGui::MenuItem("Open", "Ctrl+O")) { /* Do stuff */ }

            ImGui::NewLine();   ImGui::Separator();
            if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }

            ImGui::NewLine();   ImGui::Separator();
            if (ImGui::MenuItem("Exit", "Ctrl+W")) { quick_exit(0); }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Edit"))
        {
            ImGui::SetCursorPosX(50);
            ImGui::Text("HISTORY");  ImGui::Separator();
            if (ImGui::MenuItem("Undo", "Ctrl+Z")) { /* Do stuff */ }
            if (ImGui::MenuItem("Rendo", "Ctrl+Y")) { /* Do stuff */ }

            ImGui::NewLine();   ImGui::SetCursorPosX(60);   ImGui::Text("EDIT");   ImGui::Separator();
            if (ImGui::MenuItem("Cut", "Ctrl+X")) { /* Do stuff */ }
            if (ImGui::MenuItem("Copy", "Ctrl+C")) { /* Do stuff */ }
            if (ImGui::MenuItem("Paste", "Ctrl+V")) { /* Do stuff */ }
            if (ImGui::MenuItem("Duplicated", "Ctrl+D")) { /* Do stuff */ }
            if (ImGui::MenuItem("Delete", "DELETE")) { /* Do stuff */ }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Window"))
        {
            if (ImGui::MenuItem("Open", "Ctrl+O")) { /* Do stuff */ }
            if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
            
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Tools"))
        {
            if (ImGui::MenuItem("Open", "Ctrl+O")) { /* Do stuff */ }
            if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
            
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

}


void Details::showDetails() {

    ImGui::Begin("Details");
    ImGui::Text("hummm");
    ImGui::End();

}


void Render::showRender() {

    ImGui::Begin("Render");

    ImGui::BeginGroup();
    // 1. Le Header raccourci (on utilise TreeNodeEx pour plus de contrôle)
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, 4));
    bool open = ImGui::TreeNodeEx("Selection Mode", ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_SpanAvailWidth == false);
    ImGui::PopStyleVar();

    
    ImGui::SameLine(0);

    if (ImGui::Button("TRANSF")) { /* Do stuff0 */ }
    ImGui::SameLine();
    if (ImGui::Button("T")) { /* Do stuff1 */ }
    ImGui::SameLine();
    if (ImGui::Button("R")) { /* Do stuff2 */ }
    ImGui::SameLine();
    if (ImGui::Button("S")) { /* Do stuff3 */ }
    static int jsp = 3;
    
    if (open) {
        ImGui::Text("TANSFRORM TOOLS");    ImGui::Separator();
        ImGui::NewLine();

        if (ImGui::RadioButton("Selecte Mode", &jsp, 0)) /* Do stuff0 */;

        if (ImGui::RadioButton("Translate Mode", &jsp, 1)) /* Do stuff1 */;

        if (ImGui::RadioButton("Rotate Mode", &jsp, 2)) /* Do stuff2 */;

        if (ImGui::RadioButton("Scale Mode", &jsp, 3)) /* Do stuff3 */;
        ImGui::TreePop();
    }

    ImGui::EndGroup();


    ImGui::BeginChild(",", ImVec2(0, 0), true);
        ImGui::Text("LA OU ON VA RENDEEEEEEEEEEER");
        ImGui::EndChild();
    ImGui::End();

}