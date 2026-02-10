#include <windows.h>
#include <memory>
#include "Graphics/RenderPipeline/Renderer.h" // Ton en-tête principal

// Dimensions de la fenêtre
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// Pointeur global vers le renderer (nécessaire si on veut gérer le redimensionnement plus tard)
// Note : Dans une architecture plus avancée, on stockerait ça dans le GWLP_USERDATA de la fenêtre.
Renderer* g_renderer = nullptr;

// 1. La Procédure de Fenêtre (Gestion des événements Windows)
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE) {
            DestroyWindow(hwnd); // Ferme si on appuie sur Echap
        }
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0); // Demande l'arrêt de la boucle
        return 0;

        // Cas futur : WM_SIZE pour redimensionner la SwapChain
        // case WM_SIZE:
        //     if (g_renderer) g_renderer->OnResize(LOWORD(lParam), HIWORD(lParam));
        //     return 0;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

// 2. Point d'entrée principal (Main)
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    // A. Déclaration de la classe de fenêtre
    WNDCLASSEX wc = { 0 };
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.lpszClassName = L"DX11EngineClass";

    if (!RegisterClassEx(&wc)) {
        MessageBox(nullptr, L"Échec de l'enregistrement de la classe de fenêtre.", L"Erreur", MB_OK | MB_ICONERROR);
        return -1;
    }

    // B. Calcul de la taille réelle de la fenêtre (Client area + Bordures)
    RECT wr = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

    // C. Création de la fenêtre
    HWND hwnd = CreateWindowEx(
        0,
        L"DX11EngineClass",
        L"Moteur DX11 - Test Triangle",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        wr.right - wr.left, // Largeur ajustée
        wr.bottom - wr.top, // Hauteur ajustée
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );

    if (!hwnd) {
        MessageBox(nullptr, L"Échec de la création de la fenêtre.", L"Erreur", MB_OK | MB_ICONERROR);
        return -1;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // D. Initialisation du Renderer
    // On utilise un pointeur unique (smart pointer recommandé, mais raw pointer ok ici pour le main)
    auto renderer = std::make_unique<Renderer>();
    g_renderer = renderer.get(); // Lien global temporaire

    HRESULT hr = renderer->Initialize(hwnd, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (FAILED(hr)) {
        // Astuce : Affiche le code d'erreur hexadécimal pour faciliter le debug
        wchar_t errorMsg[256];
        swprintf_s(errorMsg, L"Échec de l'initialisation DirectX.\nCode: 0x%08X", hr);
        MessageBox(hwnd, errorMsg, L"Erreur Critique", MB_OK | MB_ICONERROR);
        return -1;
    }

    // E. La Boucle de Jeu (Game Loop)
    MSG msg = { 0 };
    while (msg.message != WM_QUIT) {
        // Si un message Windows est en attente, on le traite
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            // Sinon, on dessine la frame !
            renderer->RenderFrame();
        }
    }

    // Nettoyage (optionnel grâce aux ComPtr dans Renderer, mais bonne pratique)
    g_renderer = nullptr;

    return (int)msg.wParam;
}