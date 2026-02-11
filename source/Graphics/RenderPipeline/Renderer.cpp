#include "Graphics/RenderPipeline/Renderer.h"

HRESULT Renderer::Initialize(HWND hwnd, int width, int height) {
    HRESULT hr;

    hr = CreateDeviceAndSwapChain(hwnd, width, height);
    if (FAILED(hr)) return hr;

    hr = CreateMainViews(width, height);
    if (FAILED(hr)) return hr;

    // Configuration du Rasterizer (Cull None pour être sûr de voir le triangle)
    D3D11_RASTERIZER_DESC rd = {};
    rd.FillMode = D3D11_FILL_SOLID;
    rd.CullMode = D3D11_CULL_NONE;
    rd.DepthClipEnable = TRUE;
    m_device->CreateRasterizerState(&rd, m_rasterizerState.GetAddressOf());
    m_context->RSSetState(m_rasterizerState.Get());

    // Setup du test
    //return SetupTestTriangle();
    return S_OK;
}

void Renderer::RenderFrame() {
    float clearColor[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    m_context->ClearRenderTargetView(m_renderTargetView.Get(), clearColor);
    m_context->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);

    // Liaison des shaders de test
    m_context->VSSetShader(m_testVS.Get(), nullptr, 0);
    m_context->PSSetShader(m_testPS.Get(), nullptr, 0);

    // Utilisation de ta méthode Bind()
    m_testMesh.Bind(m_context);

    // Draw Call
    m_context->DrawIndexed(m_testMesh.GetIndexCount(), 0, 0);

    m_swapChain->Present(1, 0);
}

HRESULT Renderer::CreateDeviceAndSwapChain(HWND hwnd, int width, int height) {
    HRESULT hr;

    // 1. Description de la SwapChain (Le double buffering)
    DXGI_SWAP_CHAIN_DESC scd = {};
    scd.BufferCount = 1;                                    // 1 Back Buffer
    scd.BufferDesc.Width = width;
    scd.BufferDesc.Height = height;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // Couleur 32 bits standard
    scd.BufferDesc.RefreshRate.Numerator = 60;              // Cible 60Hz
    scd.BufferDesc.RefreshRate.Denominator = 1;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // On dessine dessus
    scd.OutputWindow = hwnd;                                // Fenêtre Windows
    scd.SampleDesc.Count = 1;                               // Pas d'anti-aliasing (MSAA)
    scd.SampleDesc.Quality = 0;
    scd.Windowed = TRUE;                                    // Mode fenêtré
    scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;              // Standard et compatible

    // 2. Flags de création (Debug Layer indispensable pour le dev)
    UINT createDeviceFlags = 0;
/*#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif*/

    // 3. Niveaux de fonctionnalités (On vise DX11 pur)
    D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 };
    D3D_FEATURE_LEVEL featureLevel;

    // 4. Création proprement dite
    hr = D3D11CreateDeviceAndSwapChain(
        nullptr,                    // Adapter par défaut
        D3D_DRIVER_TYPE_HARDWARE,   // Carte graphique réelle
        nullptr,
        createDeviceFlags,
        featureLevels,
        1,
        D3D11_SDK_VERSION,
        &scd,
        m_swapChain.GetAddressOf(),
        m_device.GetAddressOf(),
        &featureLevel,
        m_context.GetAddressOf()
    );

    if (FAILED(hr)) {
        // Astuce pro : Si ça échoue, c'est souvent parce que l'ordi n'a pas DX11 complet
        // ou que le SDK Debug n'est pas installé.
        return hr;
    }

    return S_OK;
}

HRESULT Renderer::CreateMainViews(int width, int height) {
    HRESULT hr;

    // --- A. Render Target View (Couleur) ---
    // On récupère le BackBuffer créé par la SwapChain
    Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
    hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)backBuffer.GetAddressOf());
    if (FAILED(hr)) return hr;

    // On crée la vue pour dessiner dessus
    hr = m_device->CreateRenderTargetView(backBuffer.Get(), nullptr, m_renderTargetView.GetAddressOf());
    if (FAILED(hr)) return hr;


    // --- B. Depth Stencil View (Profondeur/Z-Buffer) ---
    // 1. Description de la texture de profondeur
    D3D11_TEXTURE2D_DESC depthDesc = {};
    depthDesc.Width = width;
    depthDesc.Height = height;
    depthDesc.MipLevels = 1;
    depthDesc.ArraySize = 1;
    depthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT; // 24 bits Z, 8 bits Stencil
    depthDesc.SampleDesc.Count = 1;
    depthDesc.SampleDesc.Quality = 0;
    depthDesc.Usage = D3D11_USAGE_DEFAULT;
    depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthDesc.CPUAccessFlags = 0;
    depthDesc.MiscFlags = 0;

    // 2. Création de la texture
    Microsoft::WRL::ComPtr<ID3D11Texture2D> depthStencilBuffer;
    hr = m_device->CreateTexture2D(&depthDesc, nullptr, depthStencilBuffer.GetAddressOf());
    if (FAILED(hr)) return hr;

    // 3. Création de la vue
    hr = m_device->CreateDepthStencilView(depthStencilBuffer.Get(), nullptr, m_depthStencilView.GetAddressOf());
    if (FAILED(hr)) return hr;


    // --- C. Output Merger (Liaison finale) ---
    // On branche tout ça au contexte
    m_context->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), m_depthStencilView.Get());


    // --- D. Viewport (Zone de dessin) ---
    D3D11_VIEWPORT vp = {};
    vp.Width = (float)width;
    vp.Height = (float)height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;

    m_context->RSSetViewports(1, &vp);

    return S_OK;
}