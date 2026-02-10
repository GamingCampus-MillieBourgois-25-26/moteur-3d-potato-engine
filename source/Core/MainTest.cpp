//#ifndef UNICODE
//#define UNICODE
//#endif 
//
//#define WIN32_LEAN_AND_MEAN
//#include <windows.h>
//
//// Prototype de la fonction de gestion des messages (WndProc)
//LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//
//int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR pCmdLine, _In_ int nCmdShow){
//    // 1. Enregistrement de la classe de fenêtre
//    const wchar_t CLASS_NAME[] = L"EngineWindowClass";
//
//    WNDCLASS wc = { };
//    wc.lpfnWndProc = WindowProc;
//    wc.hInstance = hInstance;
//    wc.lpszClassName = CLASS_NAME;
//    wc.hCursor = LoadCursor(NULL, IDC_ARROW); // Curseur visible
//
//    RegisterClass(&wc);
//
//    // 2. Création de la fenêtre
//    HWND hwnd = CreateWindowEx(
//        0,                              // Style optionnel
//        CLASS_NAME,                     // Nom de la classe
//        L"C++ Game Engine - DX11",      // Titre
//        WS_OVERLAPPEDWINDOW,            // Style de fenêtre
//        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, // Position et Taille
//        NULL, NULL, hInstance, NULL
//    );
//
//    if (hwnd == NULL) return 0;
//
//    ShowWindow(hwnd, nCmdShow);
//
//    // 3. Boucle de messages (The "Heart" of the Engine)
//    MSG msg = { };
//    while (true) {
//        // Traitement des messages Windows (clavier, souris, système)
//        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
//            if (msg.message == WM_QUIT) break;
//            TranslateMessage(&msg);
//            DispatchMessage(&msg);
//        }
//        else {
//            // --- C'est ici que le moteur tourne quand il n'y a pas de message ---
//            // TODO: Appeler Engine->Update()
//            // TODO: Appeler Engine->Render()
//        }
//    }
//
//    return 0;
//}
//
//// Gestionnaire de messages
//LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
//    switch (uMsg) {
//    case WM_DESTROY:
//        PostQuitMessage(0);
//        return 0;
//
//    
//
//    case WM_PAINT: {
//        PAINTSTRUCT ps;
//        HDC hdc = BeginPaint(hwnd, &ps);
//        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
//        EndPaint(hwnd, &ps);
//    } return 0;
//    }
//    return DefWindowProc(hwnd, uMsg, wParam, lParam);
//}