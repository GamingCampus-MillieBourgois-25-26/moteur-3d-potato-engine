#include "Engine.h"

using namespace DirectX;
using Microsoft::WRL::ComPtr;

// Constantes globales
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

// Déclaration globale pour accéder à l'engine depuis le WndProc
extern PotatoEngine* g_pEngine;

// Variables globales (ImGui)
bool OpenImGui = true;
MyGui::Menu menu;
MyGui::Details details;
MyGui::Render render;
MyGui::Outliner outliner;
MyGui::findFile findfile;

//--camera--
Camera mainCamera;
auto tp1 = std::chrono::high_resolution_clock::now();


//test triangle 
static void CreateTriangle(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices) {
    vertices = {
        // Position            // Normale            // UV            // Couleur (RGBA)
        { { 0.0f,  0.5f, 0.0f }, { 0.0f, 0.0f, -1.0f }, { 0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } }, // Haut (Rouge)
        { { 0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } }, // Bas Droite (Vert)
        { { -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } }  // Bas Gauche (Bleu)
    };
    indices = { 0, 1, 2 };
}


static void CreatePyramid(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices) {
    // 1. Définition des 4 sommets (Position, Normale, UV, Couleur)
    vertices = {
        // Sommet 0 : Sommet (Haut) - Jaune
        { { 0.0f,  0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.5f, 0.0f }, { 1.0f, 1.0f, 0.0f, 1.0f } },
        // Sommet 1 : Base Avant Gauche - Rouge
        { { -0.5f, -0.5f, -0.5f }, { -1.0f, -1.0f, -1.0f }, { 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
        // Sommet 2 : Base Avant Droite - Vert
        { { 0.5f, -0.5f, -0.5f }, { 1.0f, -1.0f, -1.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
        // Sommet 3 : Base Arrière - Bleu
        { { 0.0f, -0.5f, 0.5f }, { 0.0f, -1.0f, 1.0f }, { 0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f } }
    };

    // 2. Définition des faces (3 indices par triangle)
    // On doit définir chaque face dans le sens des aiguilles d'une montre
    indices = {
        0, 2, 1, // Face Avant
        0, 3, 2, // Face Droite
        0, 1, 3, // Face Gauche
        1, 2, 3  // Face Inférieure (Base)
    };
}

// Procédure de fenêtre
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// 1. Procédure de fenêtre (Gestion des événements)
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam))
        return true;

    switch (msg) {
    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE) DestroyWindow(hwnd);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

// Initialisation
void PotatoEngine::Initialize(HINSTANCE hInstance, int nCmdShow) {
    m_hInstance = hInstance;

    // Enregistrement de la classe de fenêtre
    WNDCLASSEX wc = { 0 };
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.lpszClassName = L"DX11EngineClass";

    if (!RegisterClassEx(&wc)) return ;

    // Création de la fenêtre
    RECT wr = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);


    m_hwnd = CreateWindowEx(0, L"DX11EngineClass", L"Potato Engine - Render Test",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        wr.right - wr.left, wr.bottom - wr.top,
        nullptr, nullptr, hInstance, nullptr);

    if (!m_hwnd) {
        MessageBox(nullptr, L"Erreur : Création fenêtre échouée", L"Erreur", MB_ICONERROR);
        return;
    }

    ShowWindow(m_hwnd, nCmdShow);
}

// Boucle principale
void PotatoEngine::run() {
    FileParser fp;
    fp.OpenAllOBJ();


    // Initialisation Renderer
    auto renderer = std::make_unique<Renderer>();
    HRESULT hrInit = renderer->Initialize(m_hwnd, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (FAILED(hrInit)) {
        // Si on entre ici, c'est l'init du GPU qui foire
        MessageBox(nullptr, L"Échec Initialisation GPU (Renderer).", L"Erreur DirectX", MB_ICONERROR);
        return ;
    }

    auto device = renderer->GetDevice();
    if (!device) {
        MessageBox(nullptr, L"Le Device DirectX est NUL !", L"Erreur Fatale", MB_ICONERROR);
        return ;
    }

    // Chargement des Shaders
    ComPtr<ID3D11VertexShader> vertexShader;
    ComPtr<ID3D11PixelShader> pixelShader;
    ComPtr<ID3DBlob> vsBlob;

    if (FAILED(ShaderManager::CreateVertexShader(
        renderer->GetDevice(),
        L"Shaders/VertexShader.hlsl", // Chemin relatif à l'EXE
        vertexShader,
        vsBlob)))
    {
        MessageBox(m_hwnd, L"Erreur : Dossier 'Shaders' introuvable à côté de l'EXE.", L"Potato Engine", MB_ICONERROR);
        return ;
    }

    if (FAILED(ShaderManager::CreatePixelShader(
        renderer->GetDevice(),
        L"Shaders/PixelShader.hlsl", // Chemin relatif à l'EXE
        pixelShader)))
    {
        return ;
    }

    if (FAILED(renderer->CreateDefaultInputLayout(vsBlob.Get()))) {

        MessageBox(m_hwnd, L"Erreur : Impossible de créer l'Input Layout.", L"Renderer Error", MB_ICONERROR);
        return ;

    }

    // --- D. Préparation de la scène (Une seule fois avant la boucle) ---

    SceneManager& sceneManager = SceneManager::Get();
    sceneManager.NewScene();

    // Cube 1 - Position gauche
    Actor& actor1 = sceneManager.GetCurrent().CreateActor("Cube1");
    actor1.AddComponent<MeshComponent>();
    auto* mc1 = actor1.GetComponent<MeshComponent>();
    mc1->SetMesh(Buffers::Get().GetMesh("Cube.obj"));
    mc1->SetVertexShader(vertexShader.Get());
    mc1->SetPixelShader(pixelShader.Get());
    mc1->SetWorldMatrix(DirectX::XMMatrixTranslation(-1.5f, 0.0f, 0.0f)); //  gauche

    // Cube 2 - Position droite
    Actor& actor2 = sceneManager.GetCurrent().CreateActor("Cube2");
    actor2.AddComponent<MeshComponent>();
    auto* mc2 = actor2.GetComponent<MeshComponent>();
    mc2->SetMesh(Buffers::Get().GetMesh("Cube.obj"));
    mc2->SetVertexShader(vertexShader.Get());
    mc2->SetPixelShader(pixelShader.Get());
    mc2->SetWorldMatrix(DirectX::XMMatrixTranslation(1.5f, 0.0f, 0.0f));  //  droite


    std::vector<MeshComponent*> sceneItems;

    for (auto& pair : sceneManager.GetCurrent().GetActors())
    {
        if (pair.second.HasComponent<MeshComponent>()) {
            // On récupère l'adresse du composant réel
            sceneItems.push_back(pair.second.GetComponent<MeshComponent>());
            std::cout << "feur" << std::endl;
        }
    }

    // Physics Init

	PhysicsSystem physicsSystem;
	physicsSystem.Init();

    PhysicsBodyFactory physicsFactory;
    
    actor1.AddComponent<PhysicsBody>(physicsFactory.CreateBody(physicsSystem, PhysicsBodyType::Dynamic, BoxShape(Maths::Vec3(10, 10, 10)), 10, Maths::Vec3(0, 0, 0), Maths::Quat(0, 0, 0, 0)));

    // ImGui Init
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplWin32_Init(m_hwnd);
    ImGui_ImplDX11_Init(renderer->GetDevice().Get(), renderer->GetContext().Get());

    // Boucle de jeu
    MSG msg = { 0 };
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {

			// Physics Update
            
            physicsSystem.Update();

            // --- 1. GESTION DU TEMPS ---
            auto tp2 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> elapsedTime = tp2 - tp1;
            tp1 = tp2;
            float dt = elapsedTime.count();

            // --- 2. INPUTS ET MISE À JOUR CAMÉRA ---
            ImGuiIO& io = ImGui::GetIO();

            // On vérifie si la souris est sur la fenêtre du Viewport pour ne pas bouger 
            // la caméra quand on clique sur l'Outliner ou les Détails
            bool canMoveCamera = ImGui::IsMouseDown(ImGuiMouseButton_Right) && !ImGuizmo::IsUsing();

            mainCamera.Update(dt, canMoveCamera, io.MouseDelta.x, io.MouseDelta.y);

            // --- 3. RÉCUPÉRATION DES MATRICES ---
            XMMATRIX viewMatrix = mainCamera.GetViewMatrix();
            XMMATRIX projectionMatrix = XMMatrixPerspectiveFovLH(XM_PIDIV4, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 1000.0f);

            // Mise à jour pour le Gizmo
            render.gizmo.viewMatrix = viewMatrix;
            render.gizmo.projectionMatrix = projectionMatrix;

            // --- 4. FRAME IMGUI ---
            ImGui_ImplDX11_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();
            ImGuizmo::BeginFrame();

            menu.barMenu();

            // Viewport
            ImGui::SetNextWindowPos(ImVec2(5, 25), ImGuiCond_Once);
            ImGui::SetNextWindowSize(ImVec2(1200, 700), ImGuiCond_Once);
            ImGui::Begin("Game Viewport");
            {
                render.showRender();
                ImVec2 viewportSize = ImGui::GetContentRegionAvail();
                ImGui::Image((void*)renderer->GetSceneSRV(), viewportSize);

                ImVec2 imagePos = ImGui::GetItemRectMin();
                //render.gizmo.drawGizmo(imagePos, viewportSize, viewMatrix, projectionMatrix, triItem.worldMatrix);
            }
            ImGui::End();

            // ? DEBUG: Affiche si les matrices sont valides
            if (ImGui::Begin("Debug")) {
                ImGui::Text("View Matrix valid: %s", render.gizmo.viewMatrix.r[0].m128_f32[0] != 0 ? "Yes" : "No");
                ImGui::Text("Proj Matrix valid: %s", render.gizmo.projectionMatrix.r[0].m128_f32[0] != 0 ? "Yes" : "No");
                ImGui::End();
            }


            details.showDetails();
            outliner.showOutliner();
            findfile.showFindFile();
            

            // --- 5. RENDU FINAL ---
            PerFrameCB frameData;
            frameData.viewMatrix = viewMatrix;
            frameData.projectionMatrix = projectionMatrix;

            renderer->RenderFrame(frameData, sceneItems);
            renderer->GetContext()->OMSetRenderTargets(1, renderer->GetMainRTVAddress(), nullptr);

            float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
            renderer->GetContext()->ClearRenderTargetView(*renderer->GetMainRTVAddress(), clearColor);
            renderer->GetContext()->RSSetState(nullptr); // Reset Rasterizer
            renderer->GetContext()->OMSetDepthStencilState(nullptr, 0); // Désactive le Depth Test

            ImGui::Render();
            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

            renderer->Present();
        }
    }

    // Cleanup
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}