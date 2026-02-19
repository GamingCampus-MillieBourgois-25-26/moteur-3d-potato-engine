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
            
            ImGui::SeparatorText("HISTORY");  
            if (ImGui::MenuItem("Undo", "Ctrl+Z")) { /* Do stuff */ }
            if (ImGui::MenuItem("Rendo", "Ctrl+Y")) { /* Do stuff */ }

            ImGui::NewLine();   ImGui::SeparatorText("EDIT");
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

    if (ImGui::InputText("Search", searchRubric, sizeof(searchRubric))) /* Do stuff0 */;

    // Transform 
    {

        if (ImGui::CollapsingHeader("Transformers", ImGuiTreeNodeFlags_DefaultOpen)) {

            ImGui::Columns(4, "transform_columns", true);
            ImGui::SetColumnWidth(0, 125);

            ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 3.0f); // Arrondi léger style Unreal

            // first line
            {

                // --- Ligne Translation ---
                ImGui::AlignTextToFramePadding();
                ImGui::LabelText("", "Translation");

                ImGui::NextColumn();
                if (ImGui::BeginChild("##1trans_box", ImVec2(-1, 25), true, ImGuiWindowFlags_NoScrollbar)) {
                    ImGui::Text("0000.0");
                }
                ImGui::EndChild();

                ImGui::NextColumn();
                if (ImGui::BeginChild("##2trans_box", ImVec2(-1, 25), true, ImGuiWindowFlags_NoScrollbar)) {
                    ImGui::Text("0000.0");
                }
                ImGui::EndChild();

                ImGui::NextColumn();
                if (ImGui::BeginChild("##3trans_box", ImVec2(-1, 25), true, ImGuiWindowFlags_NoScrollbar)) {
                    ImGui::Text("0000.0");
                }

                ImGui::EndChild();
                ImGui::Separator();
                ImGui::NextColumn();
            }

            // second line
            {

                // --- Ligne Rotation ---
                ImGui::AlignTextToFramePadding();
                ImGui::LabelText("", "Rotation");

                ImGui::NextColumn();
                if (ImGui::BeginChild("##1rot_box", ImVec2(-1, 25), true, ImGuiWindowFlags_NoScrollbar)) {
                    ImGui::Text("0000.0");
                }
                ImGui::EndChild();

                ImGui::NextColumn();
                if (ImGui::BeginChild("##2rot_box", ImVec2(-1, 25), true, ImGuiWindowFlags_NoScrollbar)) {
                    ImGui::Text("0000.0");
                }
                ImGui::EndChild();

                ImGui::NextColumn();
                if (ImGui::BeginChild("##3rot_box", ImVec2(-1, 25), true, ImGuiWindowFlags_NoScrollbar)) {
                    ImGui::Text("0000.0");
                }

                ImGui::EndChild();
                ImGui::Separator();
                ImGui::NextColumn();
            }

            // third line
            {

                // --- Ligne Scale ---
                ImGui::AlignTextToFramePadding();
                ImGui::LabelText("", "Scale");

                ImGui::NextColumn();
                if (ImGui::BeginChild("##1scale_box", ImVec2(-1, 25), true, ImGuiWindowFlags_NoScrollbar)) {
                    ImGui::Text("0000.0");
                }
                ImGui::EndChild();

                ImGui::NextColumn();
                if (ImGui::BeginChild("##2scale_box", ImVec2(-1, 25), true, ImGuiWindowFlags_NoScrollbar)) {
                    ImGui::Text("0000.0");
                }
                ImGui::EndChild();

                ImGui::NextColumn();
                if (ImGui::BeginChild("##3scale_box", ImVec2(-1, 25), true, ImGuiWindowFlags_NoScrollbar)) {
                    ImGui::Text("0000.0");
                }

                ImGui::EndChild();
                ImGui::Separator();
            }

            ImGui::PopStyleVar();
            ImGui::Columns(1);
        }

    }

    //Physics
    
    if (ImGui::CollapsingHeader("Physics"))
    {
        ImGui::Columns(2, "physics_columns", true);

        ImGui::AlignTextToFramePadding();
        ImGui::LabelText("", "Simulate Physics");

        ImGui::NextColumn();

        if (ImGui::Checkbox(" ", &isPhysicsActiv)) /* Do stuff0 */;

        ImGui::Columns(1);
    }


    ImGui::End();
}


void Render::showRender() {

    ImGui::Begin("Render");

    // Selected Transform
    {

        ImGui::BeginGroup();
        // 1. Le Header raccourci (on utilise TreeNodeEx pour plus de contrôle)
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, 4));
        bool open = ImGui::TreeNodeEx("Selection Mode", ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_SpanAvailWidth == false);
        ImGui::PopStyleVar();

        ImGui::SameLine(0);

        //Transform button
        {

            if (ImGui::Button("TRANSF")) { jsp = 0; /* Do stuff0 */ }
            ImGui::SameLine();
            if (ImGui::Button("T")) { jsp = 1; /* Do stuff1 */ }
            ImGui::SameLine();
            if (ImGui::Button("R")) { jsp = 2; /* Do stuff2 */ }
            ImGui::SameLine();
            if (ImGui::Button("S")) { jsp = 3; /* Do stuff3 */ }

        }

        //Radio Transform button
        {
            if (open) {
                ImGui::SeparatorText("TANSFRORM TOOLS");

                if (ImGui::RadioButton("Selecte Mode", &jsp, 0)) /* Do stuff0 */;

                if (ImGui::RadioButton("Translate Mode", &jsp, 1)) /* Do stuff1 */;

                if (ImGui::RadioButton("Rotate Mode", &jsp, 2)) /* Do stuff2 */;

                if (ImGui::RadioButton("Scale Mode", &jsp, 3)) /* Do stuff3 */;
                ImGui::TreePop();
            }
        }

        ImGui::EndGroup();

    }
    
    //Render
    {

        ImGui::BeginChild(",", ImVec2(0, 0), true);
        ImGui::Text("LA OU ON VA RENDEEEEEEEEEEER");
        ImGui::EndChild();

    }
    
    ImGui::End();
}

void Outliner::showOutliner() {

    ImGui::Begin("Outliner");
    
    if (ImGui::InputText("Search", searchItem, sizeof(searchItem))) /* Do stuff0 */;

	ImGui::Columns(2, "outliner_columns", true);

    ImGui::AlignTextToFramePadding();
    ImGui::LabelText("", "Show Items");

	if (ImGui::Checkbox(" ", &showActor)) /* Do stuff0 */;
    if (ImGui::Checkbox("  ", &showActor)) /* Do stuff1 */;

	ImGui::NextColumn();
    ImGui::LabelText("", "Items");

    if (ImGui::Button("Item 1")) /* Do stuff0 */;
    if (ImGui::Button("Item 2")) /* Do stuff1 */;
    


    ImGui::Columns(1);

    ImGui::End();

}