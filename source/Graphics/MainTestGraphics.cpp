#include <windows.h>
#include <memory>
#include <vector>
#include <DirectXMath.h>

// En-têtes de ton moteur
#include "Graphics/RenderPipeline/Renderer.h"


using namespace DirectX;
using Microsoft::WRL::ComPtr;

// Dimensions de la fenêtre
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

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

// 1. Procédure de fenêtre (Gestion des événements)
/*LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
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

    // 2. Préparation des données géométriques
    std::vector<Vertex> triVertices;
    std::vector<uint32_t> triIndices;
   
    CreateTriangle(triVertices, triIndices);

    // 3. Création et initialisation du Mesh
    auto triangleMesh = std::make_unique<MeshBuffer>();
    if (FAILED(triangleMesh->Initialize(renderer->GetDevice(), triVertices, triIndices))) {
        return -1;
    }

    // 4. Création de l'Input Layout (Liaison entre Vertex.h et le Shader)
    if (FAILED(triangleMesh->CreateInputLayout(renderer->GetDevice(), vsBlob->GetBufferPointer(), vsBlob->GetBufferSize()))) {
        return -1;
    }

    // --- D. Préparation de la scène (Une seule fois avant la boucle) ---

    std::vector<RenderItem> sceneItems;

    RenderItem triItem;
    triItem.mesh = triangleMesh.get(); // Utilisation du pointeur brut pour le rendu
    triItem.vs = vertexShader.Get();
    triItem.ps = pixelShader.Get();
    triItem.worldMatrix = DirectX::XMMatrixIdentity();
    triItem.color = { 0.2f, 0.7f, 0.9f, 1.0f };

    sceneItems.push_back(triItem);

    // --- E. Boucle de Jeu ---
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

            frameData.viewMatrix = XMMatrixLookAtLH(eye, at, up);
            frameData.projectionMatrix = XMMatrixPerspectiveFovLH(XM_PIDIV4, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

            // 2. Appel au Renderer
            renderer->RenderFrame(frameData, sceneItems);
        }
    }
    //return (int)msg.wParam;
}
*/
