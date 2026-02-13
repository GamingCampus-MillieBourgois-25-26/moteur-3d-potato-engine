#include <windows.h>
#include <memory>
#include <vector>
#include <DirectXMath.h>

// En-têtes de ton moteur
#include "Graphics/RenderPipeline/Renderer.h"
#include "Graphics/RenderPipeline/ShaderManager.h"
#include "Graphics/RenderPipeline/MeshBuffer.h"

using namespace DirectX;
using Microsoft::WRL::ComPtr;

// Dimensions de la fenêtre
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// 1. Procédure de fenêtre (Gestion des événements)
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
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
   /* if (FAILED(ShaderManager::CreateVertexShader(
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

    // 2. Création du Mesh (Un triangle de test)
    MeshBuffer triangleMesh;
    std::vector<Vertex> vertices = {
        { { 0.0f, 0.5f, 0.0f },  { 0.0f, 0.0f, -1.0f }, { 0.5f, 0.0f } }, // Haut
        { { 0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f } }, // Bas Droite
        { { -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f } }  // Bas Gauche
    };
    std::vector<uint32_t> indices = { 0, 1, 2 };

    if (FAILED(triangleMesh.Initialize(renderer->GetDevice(), vertices, indices))) {
        MessageBox(nullptr, L"Erreur Initialize Mesh", L"Erreur", MB_OK);
        return -1;
    }
    if (FAILED(triangleMesh.CreateInputLayout(renderer->GetDevice(), vsBlob->GetBufferPointer(), vsBlob->GetBufferSize()))) {
        MessageBox(nullptr, L"Erreur CreateInputLayout", L"Erreur", MB_OK);
        return -1;
    }*/
    // --- D. Boucle de Jeu ---
    MSG msg = { 0 };
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            // 1. Mise à jour de la Caméra (PerFrame)
            PerFrameCB frameData;
            XMVECTOR eye = XMVectorSet(0.0f, 0.0f, -2.0f, 0.0f);
            XMVECTOR at = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
            XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

            // On ne transpose pas ici, le Renderer s'en chargera dans RenderFrame
            frameData.viewMatrix = XMMatrixLookAtLH(eye, at, up);
            frameData.projectionMatrix = XMMatrixPerspectiveFovLH(XM_PIDIV4, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

            // 2. Préparation de la liste d'objets (RenderItem)
            // Goulot d'étranglement potentiel : Ne pas réallouer ce vecteur à chaque frame en prod.
            /*RenderItem tri;
            tri.mesh = &triangleMesh;
            tri.vs = vertexShader.Get();
            tri.ps = pixelShader.Get();
            tri.worldMatrix = XMMatrixIdentity();
            tri.color = XMFLOAT4(0.2f, 0.7f, 0.9f, 1.0f);*/ // Bleu clair

            std::vector<RenderItem> sceneItems;
            //sceneItems.push_back(tri);

            // 3. Rendu
            renderer->RenderFrame(frameData, sceneItems);
        }
    }

    return (int)msg.wParam;
}