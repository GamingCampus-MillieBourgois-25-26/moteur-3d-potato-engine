#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"


#ifndef UNICODE
#define UNICODE
#endif 

#define WIN32_LEAN_AND_MEAN
#include <windows.h>


#include <d3d11.h>

#pragma comment(lib, "d3d11.lib")

// --- VARIABLES GLOBALES DX11 (Pour le test) ---
ID3D11Device* g_pd3dDevice = nullptr;
ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
IDXGISwapChain* g_pSwapChain = nullptr;
ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;

// --- FONCTION DE SETUP DX11 ---
bool CreateDeviceD3D(HWND hWnd) {
    DXGI_SWAP_CHAIN_DESC sd = {};
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0 };

    HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (FAILED(hr)) return false;

    // Création de la Render Target
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
    pBackBuffer->Release();
    return true;

}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool testImGui = true;

// Prototype de la fonction de gestion des messages (WndProc)
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR pCmdLine, _In_ int nCmdShow){
    // 1. Enregistrement de la classe de fenêtre
    const wchar_t CLASS_NAME[] = L"EngineWindowClass";

    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW); // Curseur visible

    RegisterClass(&wc);

    // 2. Création de la fenêtre
    HWND hwnd = CreateWindowEx(
        0,                              // Style optionnel
        CLASS_NAME,                     // Nom de la classe
        L"C++ Game Engine - DX11",      // Titre
        WS_OVERLAPPEDWINDOW,            // Style de fenêtre
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, // Position et Taille
        NULL, NULL, hInstance, NULL
    );

    if (hwnd == NULL) return 0;


    // 2. Initialiser DirectX 11 (Indispensable pour voir ImGui)
    if (!CreateDeviceD3D(hwnd)) return 1;


    ShowWindow(hwnd, nCmdShow);


    // --- INIT IMGUI ---

    // 3. Initialiser ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);


    // 3. Boucle de messages (The "Heart" of the Engine)
    MSG msg = { };
    while (true) {
        // Traitement des messages Windows (clavier, souris, système)
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            // --- C'est ici que le moteur tourne quand il n'y a pas de message ---
            // TODO: Appeler Engine->Update()
            // TODO: Appeler Engine->Render()


            // --- START IMGUI FRAME ---
            // --- START FRAME ---
            ImGui_ImplDX11_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();

            // --- TA GUI ---
            ImGui::Begin("Debug Menu", &testImGui, ImGuiWindowFlags_MenuBar);
            if (ImGui::BeginMenuBar()) {

                if (ImGui::BeginMenu("file"))
                {
                    if (ImGui::MenuItem("Open", "Ctrl+O")) { /* Do stuff */ }
                    if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
                    if (ImGui::MenuItem("Close", "Ctrl+W")) { quick_exit(0); }
                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar();
            }
            ImGui::Text("Hello Team! Le moteur est en marche.");
            static float clear_color[4] = { 0.45f, 0.55f, 0.60f, 1.00f };
            ImGui::ColorEdit3("Fond Ecran", clear_color);
            if (ImGui::Button("Test Alerte")) {
                MessageBox(hwnd, L"Ça marche !", L"Succès", MB_OK);
            }
            ImGui::End();

            // --- RENDU ---
            ImGui::Render();

            // On nettoie l'écran avec la couleur choisie
            g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
            g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color);

            // On dessine ImGui
            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

            // On affiche le résultat
            g_pSwapChain->Present(1, 0);
        }

    }
    
    // Cleanup
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    if (g_mainRenderTargetView) g_mainRenderTargetView->Release();
    if (g_pSwapChain) g_pSwapChain->Release();
    if (g_pd3dDeviceContext) g_pd3dDeviceContext->Release();
    if (g_pd3dDevice) g_pd3dDevice->Release();

    return 0;
}

// Gestionnaire de messages
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    // C'EST ESSENTIEL POUR LE CLIC SOURIS
    if (ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam))
        return true;

    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH)GetStockObject(BLACK_BRUSH));
        EndPaint(hwnd, &ps);
    } return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}