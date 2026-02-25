//#ifndef UNICODE
//#define UNICODE
//#endif
//
//#define WIN32_LEAN_AND_MEAN
//#include <cstdio>
//#include <fcntl.h>
//#include <io.h>
//#include <windows.h>
//
//#include "Physics/physicsSystem.h"
//
//// Prototype de la fonction de gestion des messages (WndProc)
//LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//
//// --- Console helper ---
//void CreateConsole()
//{
//    AllocConsole();
//
//    FILE* fp;
//    freopen_s(&fp, "CONOUT$", "w", stdout);
//    freopen_s(&fp, "CONOUT$", "w", stderr);
//    freopen_s(&fp, "CONIN$", "r", stdin);
//
//    SetConsoleTitleA("Potato Engine Console");
//}
//
//int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR pCmdLine, _In_ int nCmdShow)
//{
//    //  Cr�e la console AVANT tout log
//    CreateConsole();
//
//    printf("Console initialisee\n");
//
//    // 1. Enregistrement de la classe de fen�tre
//    const wchar_t CLASS_NAME[] = L"EngineWindowClass";
//
//    WNDCLASS wc = {};
//    wc.lpfnWndProc = WindowProc;
//    wc.hInstance = hInstance;
//    wc.lpszClassName = CLASS_NAME;
//    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
//
//    RegisterClass(&wc);
//
//    // 2. Cr�ation de la fen�tre
//    HWND hwnd = CreateWindowEx(0, CLASS_NAME, L"C++ Game Engine - DX11", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);
//
//    if (hwnd == NULL)
//        return 0;
//
//    ShowWindow(hwnd, nCmdShow);
//
//    // 3. Boucle de messages
//    MSG msg = {};
//    //a supprimer tests
//    //Physics::mainTests();
//    JPH::RegisterDefaultAllocator();
//    PhysicsSystem system;
//    system.Init();
//
//    while (true)
//    {
//        system.Update();
//        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
//        {
//            if (msg.message == WM_QUIT)
//                break;
//
//            TranslateMessage(&msg);
//            DispatchMessage(&msg);
//        }
//        else
//        {
//            // Engine Update / Render
//        }
//    }
//
//    return 0;
//}
//
//// Gestionnaire de messages
//LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//{
//    switch (uMsg)
//    {
//    case WM_DESTROY:
//        PostQuitMessage(0);
//        return 0;
//
//    case WM_PAINT:
//        {
//            PAINTSTRUCT ps;
//            HDC hdc = BeginPaint(hwnd, &ps);
//            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
//            EndPaint(hwnd, &ps);
//        }
//        return 0;
//    }
//    return DefWindowProc(hwnd, uMsg, wParam, lParam);
//}
