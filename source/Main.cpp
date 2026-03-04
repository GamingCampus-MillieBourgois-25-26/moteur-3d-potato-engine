#include <windows.h>
#include <iostream>
#include <thread>
#include <memory>
#include <vector>
#include <DirectXMath.h>

// En-têtes de ton moteur
#include "Graphics/RenderPipeline/Renderer.h"
#include "Graphics/FileParser.h"
#include "Logic/SceneManager.h"
#include "Logic/MeshComponent.h"

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "Core/ImGui/imgui_function.h"

using namespace DirectX;
using Microsoft::WRL::ComPtr;

// Dimensions de la fenêtre
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

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

// ---- IMGUI WindoW ----
bool OpenImGui = true;
MyGui::Menu menu;
MyGui::Details details/*(1460, 710, 450, 300)*/;
MyGui::Render render;
MyGui::Outliner outliner;
MyGui::findFile findfile;


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

// 2. Point d'entrée principal
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    FileParser fp;

    // --- A. Initialisation de la fenêtre Windows ---
    WNDCLASSEX wc = { 0 };
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.lpszClassName = L"DX11EngineClass";

    if (!RegisterClassEx(&wc)) return -1;

    RECT wr = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

    HWND hwnd = CreateWindowEx(0, L"DX11EngineClass", L"Potato Engine - Render Test",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        wr.right - wr.left, wr.bottom - wr.top,
        nullptr, nullptr, hInstance, nullptr);

    if (!hwnd) return -1;

    ShowWindow(hwnd, nCmdShow);

    // --- B. Initialisation du Renderer ---
    auto renderer = std::make_unique<Renderer>();
    HRESULT hrInit = renderer->Initialize(hwnd, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (FAILED(hrInit)) {
        // Si on entre ici, c'est l'init du GPU qui foire
        MessageBox(nullptr, L"Échec Initialisation GPU (Renderer).", L"Erreur DirectX", MB_ICONERROR);
        return -1;
    }

    auto device = renderer->GetDevice();
    if (!device) {
        MessageBox(nullptr, L"Le Device DirectX est NUL !", L"Erreur Fatale", MB_ICONERROR);
        return -1;
    }

    // --- C. Chargement des Ressources (Simulation d'un gestionnaire de ressources) ---


    // 1. Compilation et création des Shaders
    ComPtr<ID3D11VertexShader> vertexShader;
    ComPtr<ID3D11PixelShader> pixelShader;
    ComPtr<ID3DBlob> vsBlob; // Nécessaire pour l'Input Layout


    // 1. Chargement du Vertex Shader
// Note : vsBlob est nécessaire pour créer l'InputLayout juste après.
    if (FAILED(ShaderManager::CreateVertexShader(
        renderer->GetDevice(),
        L"Shaders/VertexShader.hlsl", // Chemin relatif à l'EXE
        vertexShader,
        vsBlob)))
    {
        MessageBox(hwnd, L"Erreur : Dossier 'Shaders' introuvable à côté de l'EXE.", L"Potato Engine", MB_ICONERROR);
        return -1;
    }

    if (FAILED(ShaderManager::CreatePixelShader(
        renderer->GetDevice(),
        L"Shaders/PixelShader.hlsl", // Chemin relatif à l'EXE
        pixelShader)))
    {
        return -1;
    }

    if (FAILED(renderer->CreateDefaultInputLayout(vsBlob.Get()))) {
     
            MessageBox(hwnd, L"Erreur : Impossible de créer l'Input Layout.", L"Renderer Error", MB_ICONERROR);
            return -1;
        
    }


    // --- D. Préparation de la scène (Une seule fois avant la boucle) ---

    SceneManager& sceneManager = SceneManager::Get();

    sceneManager.NewScene();

	// Création d'un acteur avec un MeshComponent - Pour les tests
    Actor& actor = sceneManager.GetCurrent().CreateActor("Actor1");
    actor.AddComponent<MeshComponent>();
    actor.GetComponent<MeshComponent>()->SetMesh(Buffers::Get().GetMesh("Cube.obj"));

    std::vector<MeshComponent*> sceneItems;

    for (auto& pair : sceneManager.GetCurrent().GetActors())
    {
        if (pair.second.HasComponent<MeshComponent>()) {
            // On récupère l'adresse du composant réel
            sceneItems.push_back(pair.second.GetComponent<MeshComponent>());
            std::cout << "feur" << std::endl;
        }
    }




    


    // --- IMGUI INIT ---
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark(); // Ou StyleColorsLight()

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(renderer->GetDevice().Get(), renderer->GetContext().Get());

    // --- E. Boucle de Jeu ---
    MSG msg = { 0 };
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            // 1. Démarrer la frame ImGui
            ImGui_ImplDX11_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();

            // 2. TA FENÊTRE IMGUI ICI
            {
                
                menu.barMenu();

                /*ImGui::Begin("Debug Menu", &OpenImGui, ImGuiWindowFlags_MenuBar);


                static float clear_color[4] = { 0.45f, 0.55f, 0.60f, 1.00f };
                ImGui::ColorEdit3("Fond Ecran", clear_color);
                if (ImGui::Button("Test Alerte")) {
                    MessageBox(hwnd, L"Ça marche !", L"Succès", MB_OK);
                }

                ImGui::End();*/

                ImGui::SetNextWindowPos(ImVec2(5, 25), ImGuiCond_Once);
                ImGui::SetNextWindowSize(ImVec2(1200, 700), ImGuiCond_Once);
                ImGui::Begin("Game Viewport");
                {
                    render.showRender();
                    // On récupère la taille de la fenêtre ImGui actuelle
                    ImVec2 viewportSize = ImGui::GetContentRegionAvail();

                    // On affiche la texture du renderer
                    // Note : On passe le pointeur SRV qu'on a créé
                    ImGui::Image((void*)renderer->GetSceneSRV(), viewportSize);
                }
                ImGui::End();

                details.showDetails();

                outliner.showOutliner();

                findfile.showFindFile();
            }

            // 3. Mise à jour de la Caméra (PerFrame)
            PerFrameCB frameData;
            XMVECTOR eye = XMVectorSet(1.5f, 1.0f, 5.0f, 0.0f);
            XMVECTOR at = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
            XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);


            frameData.viewMatrix = XMMatrixLookAtLH(eye, at, up);
            frameData.projectionMatrix = XMMatrixPerspectiveFovLH(XM_PIDIV4, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

            // 4. Appel au Renderer
            renderer->RenderFrame(frameData, sceneItems);

            // 5. RENDU IMGUI PAR-DESSUS
            // A. On cible la vraie fenêtre
            renderer->GetContext()->OMSetRenderTargets(1, renderer->GetMainRTVAddress(), nullptr);

            // B. INDISPENSABLE : On nettoie le buffer de la fenêtre (le fond noir derrière les fenêtres ImGui)
            float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f }; // Noir ou toute autre couleur
            renderer->GetContext()->ClearRenderTargetView(*renderer->GetMainRTVAddress(), clearColor);

            // C. On dessine ImGui
            ImGui::Render();
            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

            // 6. Present (généralement fait à la fin de RenderFrame par le SwapChain)
            // Si RenderFrame ne fait pas "m_swapChain->Present", ajoute-le ici.
            renderer->Present();

        }
    }

    // --- NETTOYAGE ---
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();


    //return (int)msg.wParam;
}

