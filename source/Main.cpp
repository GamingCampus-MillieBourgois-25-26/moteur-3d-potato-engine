#include "Engine.h"


PotatoEngine* g_pEngine = nullptr;

// Forward declare WndProc (défini dans Engine.cpp)
extern LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    PotatoEngine engine;
    g_pEngine = &engine;  // Stocke le pointeur global pour le WndProc

    engine.Initialize(hInstance, nCmdShow);
    engine.run();

}