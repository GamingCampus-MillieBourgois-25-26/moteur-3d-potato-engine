#include "Engine.h"

using namespace DirectX;
using Microsoft::WRL::ComPtr;

// Constantes globales
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

// Déclaration globale pour accéder à l'engine depuis le WndProc
extern Engine* g_pEngine;

// Variables globales (ImGui)
bool OpenImGui = true;
MyGui::Menu menu;
MyGui::Details details;
MyGui::Render render;
MyGui::Outliner outliner;
MyGui::findFile findfile;


// Fonctions utilitaires
static void CreateTriangle(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices) {
    vertices = {
        { { 0.0f,  0.5f, 0.0f }, { 0.0f, 0.0f, -1.0f }, { 0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
        { { 0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
        { { -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } }
    };
    indices = { 0, 1, 2 };
}

static void CreatePyramid(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices) {
    vertices = {
        { { 0.0f,  0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.5f, 0.0f }, { 1.0f, 1.0f, 0.0f, 1.0f } },
        { { -0.5f, -0.5f, -0.5f }, { -1.0f, -1.0f, -1.0f }, { 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
        { { 0.5f, -0.5f, -0.5f }, { 1.0f, -1.0f, -1.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
        { { 0.0f, -0.5f, 0.5f }, { 0.0f, -1.0f, 1.0f }, { 0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f } }
    };
    indices = { 0, 2, 1, 0, 3, 2, 0, 1, 3, 1, 2, 3 };
}

// Procédure de fenêtre
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

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
void Engine::Initialize(HINSTANCE hInstance, int nCmdShow) {
    m_hInstance = hInstance;

    // Enregistrement de la classe de fenêtre
    WNDCLASSEX wc = { 0 };
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.lpszClassName = L"DX11EngineClass";

    if (!RegisterClassEx(&wc)) {
        MessageBox(nullptr, L"Erreur : Enregistrement classe fenêtre échoué", L"Erreur", MB_ICONERROR);
        return;
    }

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
void Engine::run() {
    FileParser fp;
    std::shared_ptr<Mesh> caca = Buffers::Get().GetMesh("Cube.obj");

    // Initialisation Renderer
    auto renderer = std::make_unique<Renderer>();
    HRESULT hrInit = renderer->Initialize(m_hwnd, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (FAILED(hrInit)) {
        MessageBox(nullptr, L"Échec Initialisation GPU (Renderer).", L"Erreur DirectX", MB_ICONERROR);
        return;
    }

    // Chargement des Shaders
    ComPtr<ID3D11VertexShader> vertexShader;
    ComPtr<ID3D11PixelShader> pixelShader;
    ComPtr<ID3DBlob> vsBlob;

    if (FAILED(ShaderManager::CreateVertexShader(
        renderer->GetDevice(),
        L"Shaders/VertexShader.hlsl",
        vertexShader,
        vsBlob))) {
        MessageBox(m_hwnd, L"Erreur : Dossier 'Shaders' introuvable à côté de l'EXE.", L"Potato Engine", MB_ICONERROR);
        return;
    }

    if (FAILED(ShaderManager::CreatePixelShader(
        renderer->GetDevice(),
        L"Shaders/PixelShader.hlsl",
        pixelShader))) {
        return;
    }

    // Préparation du mesh
    std::vector<Vertex> triVertices;
    std::vector<uint32_t> triIndices;
    CreatePyramid(triVertices, triIndices);

    auto triangleMesh = std::make_unique<MeshBuffer>();
    if (FAILED(triangleMesh->Initialize(renderer->GetDevice(), caca->vertices, caca->indices))) {
        return;
    }

    if (FAILED(triangleMesh->CreateInputLayout(renderer->GetDevice(), vsBlob->GetBufferPointer(), vsBlob->GetBufferSize()))) {
        return;
    }

    // Préparation de la scène
    std::vector<RenderItem> sceneItems;
    RenderItem triItem;
    triItem.mesh = triangleMesh.get();
    triItem.vs = vertexShader.Get();
    triItem.ps = pixelShader.Get();
    triItem.worldMatrix = DirectX::XMMatrixIdentity();
    triItem.color = { 0.2f, 0.7f, 0.9f, 1.0f };
    sceneItems.push_back(triItem);

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
            // ImGui Frame
            ImGui_ImplDX11_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();
            ImGuizmo::BeginFrame();
     
            XMVECTOR eye = XMVectorSet(1.5f, 1.0f, 5.0f, 0.0f);
            XMVECTOR at = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
            XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

            XMMATRIX viewMatrix = XMMatrixLookAtLH(eye, at, up);
            XMMATRIX projectionMatrix = XMMatrixPerspectiveFovLH(XM_PIDIV4, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

            render.gizmo.viewMatrix = viewMatrix;
            render.gizmo.projectionMatrix = projectionMatrix;

            menu.barMenu();

            ImGui::SetNextWindowPos(ImVec2(5, 25), ImGuiCond_Once);
            ImGui::SetNextWindowSize(ImVec2(1200, 700), ImGuiCond_Once);
            ImGui::Begin("Game Viewport");
            {
                // 1. Affiche la barre d'outils (T, R, S)
                render.showRender();

                // 2. Récupère la taille restante pour l'image
                ImVec2 viewportSize = ImGui::GetContentRegionAvail();

                // 3. Affiche l'image
                ImGui::Image((void*)renderer->GetSceneSRV(), viewportSize);

                // --- C'EST ICI QUE CA SE JOUE ---
                // On récupère la position exacte où l'image vient d'être dessinée
                ImVec2 imagePos = ImGui::GetItemRectMin();
                render.gizmo.drawGizmo(imagePos, viewportSize, viewMatrix, projectionMatrix, triItem.worldMatrix);

                //// DEBUG VISUEL
                //ImGui::GetWindowDrawList()->AddRect(imagePos, ImVec2(imagePos.x + viewportSize.x, imagePos.y + viewportSize.y), IM_COL32(255, 255, 0, 255));
                ImGui::Text("Gizmo Pos: %.1f, %.1f", imagePos.x, imagePos.y);
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
            

            // 4?? Utilise les MÊMES matrices pour le rendu
            PerFrameCB frameData;
            frameData.viewMatrix = viewMatrix;
            frameData.projectionMatrix = projectionMatrix;


            // Rendu
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