#include "Core/ImGui/imgui_function.h"

void MyGui::Menu::barMenu() {

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

void MyGui::Details::showDetails() {

    ImGui::SetNextWindowPos(ImVec2(winPosX, winPosY), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(winSizeX, winSizeY), ImGuiCond_Once);
    
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
                    ImGui::InputText(" ", Xpos, sizeof(Xpos));
                }
                ImGui::EndChild();

                ImGui::NextColumn();
                if (ImGui::BeginChild("##2trans_box", ImVec2(-1, 25), true, ImGuiWindowFlags_NoScrollbar)) {
                    ImGui::InputText("  ", Ypos, sizeof(Ypos));
                }
                ImGui::EndChild();

                ImGui::NextColumn();
                if (ImGui::BeginChild("##3trans_box", ImVec2(-1, 25), true, ImGuiWindowFlags_NoScrollbar)) {
                    ImGui::InputText("   ", Zpos, sizeof(Zpos));
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
                    ImGui::InputText(" ", Xaxe, sizeof(Xaxe));
                }
                ImGui::EndChild();

                ImGui::NextColumn();
                if (ImGui::BeginChild("##2rot_box", ImVec2(-1, 25), true, ImGuiWindowFlags_NoScrollbar)) {
                    ImGui::InputText("  ", Yaxe, sizeof(Yaxe));
                }
                ImGui::EndChild();

                ImGui::NextColumn();
                if (ImGui::BeginChild("##3rot_box", ImVec2(-1, 25), true, ImGuiWindowFlags_NoScrollbar)) {
                    ImGui::InputText("   ", Zaxe, sizeof(Zaxe));
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
                    ImGui::InputText(" ", Xscale, sizeof(Xscale));
                }
                ImGui::EndChild();

                ImGui::NextColumn();
                if (ImGui::BeginChild("##2scale_box", ImVec2(-1, 25), true, ImGuiWindowFlags_NoScrollbar)) {
                    ImGui::InputText("  ", Yscale, sizeof(Yscale));
                }
                ImGui::EndChild();

                ImGui::NextColumn();
                if (ImGui::BeginChild("##3scale_box", ImVec2(-1, 25), true, ImGuiWindowFlags_NoScrollbar)) {
                    ImGui::InputText("   ", Zscale, sizeof(Zscale));
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


void MyGui::Render::showRender() {

    ImGui::Columns(3, "Render_columns", false);
    ImGui::SetColumnWidth(0, 110);

    // Selected Transform
    {

        //Radio Transform button
        {
            
            if (ImGui::Button("Selection Mode")) ImGui::OpenPopup("Selection Mode popup");

            if (ImGui::BeginPopup("Selection Mode popup")) {

                ImGui::SeparatorText("TANSFRORM TOOLS");

                if (ImGui::RadioButton("Translate", (int*)&gizmo.currentOperation, ImGuizmo::TRANSLATE))
                    gizmo.currentOperation = ImGuizmo::TRANSLATE;
                ImGui::SameLine();
                if (ImGui::RadioButton("Rotate", (int*)&gizmo.currentOperation, ImGuizmo::ROTATE))
                    gizmo.currentOperation = ImGuizmo::ROTATE;
                ImGui::SameLine();
                if (ImGui::RadioButton("Scale", (int*)&gizmo.currentOperation, ImGuizmo::SCALE))
                    gizmo.currentOperation = ImGuizmo::SCALE;

                // Mode Local/World
                if (ImGui::RadioButton("Local", (int*)&gizmo.currentMode, ImGuizmo::LOCAL))
                    gizmo.currentMode = ImGuizmo::LOCAL;
                ImGui::SameLine();
                if (ImGui::RadioButton("World", (int*)&gizmo.currentMode, ImGuizmo::WORLD))
                    gizmo.currentMode = ImGuizmo::WORLD;

                ImGui::EndPopup();
            }
        }

        ImGui::NextColumn();
        ImGui::SetColumnWidth(1, 70);

        //Transform button
        {

            //if (ImGui::Button("TRANSF")) { intTransf = 0; /* Do stuff0 */ }
            //ImGui::SameLine();
            if (ImGui::Button("T")) { gizmo.currentOperation = ImGuizmo::TRANSLATE; /* Do stuff1 */ }
            ImGui::SameLine();
            if (ImGui::Button("R")) { gizmo.currentOperation = ImGuizmo::ROTATE; /* Do stuff2 */ }
            ImGui::SameLine();
            if (ImGui::Button("S")) { gizmo.currentOperation = ImGuizmo::SCALE; /* Do stuff3 */ }

        }

    }
    
}

void MyGui::Outliner::showOutliner() {

    ImGui::SetNextWindowPos(ImVec2(winPosX, winPosY), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(winSizeX, winSizeY), ImGuiCond_Once);
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


void MyGui::findFile::showFindFile() {

    ImGui::SetNextWindowPos(ImVec2(winPosX, winPosY), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(winSizeX, winSizeY), ImGuiCond_Once);

    ImGui::Begin("Find File");

    static char selectedPath[512] = "Aucun fichier selectionne";

    if (ImGui::Button("find")) {

        std::string filePath = OpenFileDialog();
        if (!filePath.empty()) {
            // Ici tu as ton chemin de fichier !
            strncpy(selectedPath, filePath.c_str(), sizeof(selectedPath));
        }
    }

    // 3. L'afficher juste en dessous dans ton interface
    ImGui::Text("Chemin actuel :");
    ImGui::SameLine(); // Pour mettre le texte sur la même ligne
    ImGui::TextColored(ImVec4(0.4f, 0.7f, 1.0f, 1.0f), selectedPath); // En bleu clair

    ImGui::End();

}

std::string MyGui::findFile::OpenFileDialog() {
    OPENFILENAMEA ofn;       // Structure de dialogue standard
    char szFile[260] = { 0 };
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "Tous les fichiers\0*.*\0Textes\0*.TXT\0";
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

    if (GetOpenFileNameA(&ofn)) {
        return std::string(ofn.lpstrFile);
    }
    return "";
}


void MyGui::Gizmo::drawGizmo(ImVec2 pos, ImVec2 size, DirectX::XMMATRIX& view, DirectX::XMMATRIX& proj, DirectX::XMMATRIX& matrix) {

    // 1. On configure l'espace de dessin
    ImGuizmo::SetOrthographic(false); // On est en Perspective
    ImGuizmo::SetDrawlist();
    ImGuizmo::SetRect(pos.x, pos.y, size.x, size.y);

    // 2. Préparation des matrices
    float view_f[16], proj_f[16], matrix_f[16];

    // IMPORTANT : Pour DirectX, on transpose souvent View et Proj pour ImGuizmo
    DirectX::XMStoreFloat4x4((DirectX::XMFLOAT4X4*)view_f, DirectX::XMMatrixTranspose(view));
    DirectX::XMStoreFloat4x4((DirectX::XMFLOAT4X4*)proj_f, DirectX::XMMatrixTranspose(proj));

    // Pour la matrice de l'objet, on essaie SANS transpose d'abord 
    // car ImGuizmo et DX11 partagent parfois le même layout mémoire pour le World
    DirectX::XMStoreFloat4x4((DirectX::XMFLOAT4X4*)matrix_f, matrix);

    // 3. Dessin
    ImGuizmo::Manipulate(
        view_f, proj_f,
        currentOperation, currentMode,
        matrix_f
    );

    // 4. Si on manipule, on ré-injecte dans la matrice d'origine
    if (ImGuizmo::IsUsing()) {
        matrix = DirectX::XMLoadFloat4x4((DirectX::XMFLOAT4X4*)matrix_f);
    }
}