#include "Core/ImGui/imgui_function.h"

void Menu::barMenu() {

    if (ImGui::BeginMenuBar()) {

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
            ImGui::Text("HISTORY");   ImGui::Separator();
            if (ImGui::MenuItem("Undo", "Ctrl+Z")) { /* Do stuff */ }
            if (ImGui::MenuItem("Rendo", "Ctrl+Y")) { /* Do stuff */ }

            ImGui::NewLine();   ImGui::Text("EDIT");   ImGui::Separator();
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

        ImGui::EndMenuBar();
    }

}


void Details::menuDetails() {

    ImGui::Begin("Details");
    ImGui::Text("hummm");
    ImGui::End();

}