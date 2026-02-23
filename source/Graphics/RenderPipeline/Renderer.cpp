#include "Graphics/RenderPipeline/Renderer.h"

HRESULT Renderer::Initialize(HWND hwnd, int width, int height) {
    HRESULT hr;

    hr = CreateDeviceAndSwapChain(hwnd, width, height);
    if (FAILED(hr)) {
        MessageBox(nullptr, L"Echec de CreateDeviceAndSwapChain.", L"Erreur DirectX", MB_ICONERROR);
        return -1;   
    }
    //return hr;


    hr = CreateMainViews(width, height);
    if (FAILED(hr)) return hr;

    // Configuration du Rasterizer (Cull None pour être sûr de voir le triangle)
    D3D11_RASTERIZER_DESC rd = {};
    rd.FillMode = D3D11_FILL_SOLID;
    rd.CullMode = D3D11_CULL_NONE;
    rd.DepthClipEnable = TRUE;
    m_device->CreateRasterizerState(&rd, m_rasterizerState.GetAddressOf());
    m_context->RSSetState(m_rasterizerState.Get());

    m_perFrameCB.Initialize(m_device);
    m_perObjectCB.Initialize(m_device);
    // Setup du test
  
    return S_OK;
}

void Renderer::RenderFrame(const PerFrameCB& frameData, const std::vector<RenderItem>& items) {
    // 1. Nettoyage des buffers (BackBuffer et Z-Buffer)
    float clearColor[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    m_context->ClearRenderTargetView(m_renderTargetView.Get(), clearColor);
    m_context->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);

    // 2. Mise à jour du Constant Buffer Global (Caméra - Slot b0)
    // On transpose pour HLSL
    PerFrameCB gpuFrameData = frameData;
    gpuFrameData.viewMatrix = DirectX::XMMatrixTranspose(frameData.viewMatrix);
    gpuFrameData.projectionMatrix = DirectX::XMMatrixTranspose(frameData.projectionMatrix);

    m_perFrameCB.Update(m_context, gpuFrameData);
    m_context->VSSetConstantBuffers(0, 1, m_perFrameCB.GetAddressOf());

    // 3. Boucle de rendu générique
    for (const auto& item : items) {
        if (!item.mesh || !item.vs || !item.ps) continue;

        // A. Mise à jour des données de l'objet (Slot b1)
        PerObjectCB objectData;
        objectData.worldMatrix = DirectX::XMMatrixTranspose(item.worldMatrix);
        objectData.meshColor = item.color;

        // On réutilise un ConstantBuffer<PerObjectCB> interne au Renderer
        m_perObjectCB.Update(m_context, objectData);
        m_context->VSSetConstantBuffers(1, 1, m_perObjectCB.GetAddressOf());
        m_context->PSSetConstantBuffers(1, 1, m_perObjectCB.GetAddressOf());

        // B. Liaison des Shaders
        m_context->VSSetShader(item.vs, nullptr, 0);
        m_context->PSSetShader(item.ps, nullptr, 0);

        // C. Liaison du Mesh et Dessin
        item.mesh->Bind(m_context);
        m_context->DrawIndexed(item.mesh->GetIndexCount(), 0, 0);
    }

    // 4. Présentation (V-Sync activé avec le 1)
    //m_swapChain->Present(1, 0);
}

HRESULT Renderer::CreateDeviceAndSwapChain(HWND hwnd, int width, int height) {
    HRESULT hr;

    // 1. Description de la SwapChain (Le double buffering)
    DXGI_SWAP_CHAIN_DESC scd = {};

    scd.BufferDesc.Width = width; // Largeur du buffer
    scd.BufferDesc.Height = height; // Hauteur du buffer
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // Format du buffer
    scd.BufferDesc.RefreshRate.Numerator = 60; // Taux de rafraîchissement (numérateur)
    scd.BufferDesc.RefreshRate.Denominator = 1; // Taux de rafraîchissement (dénominateur)
    scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED; // Type de scaling
    scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; // Ordre de balayage
    scd.SampleDesc.Count = 1; // Nombre d'échantillons pour l'anti-aliasing
    scd.SampleDesc.Quality = 0; // Qualité de l'anti-aliasing
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // Usage du buffer
    scd.BufferCount = 1; // Nombre de buffers
    scd.OutputWindow = hwnd; // Fenêtre de sortie
    scd.Windowed = TRUE; // Mode fenêtré
    scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // Effet de swap
    scd.Flags = 0; // Flags supplémentaires



    // 3. Niveaux de fonctionnalités (On vise DX11 pur)
    D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 };
    D3D_FEATURE_LEVEL featureLevel;

    // 4. Création proprement dite
    hr = D3D11CreateDeviceAndSwapChain(
        searchForAdapters(), // Adapter
        D3D_DRIVER_TYPE_UNKNOWN,// Driver Type
        nullptr,
        0,
        nullptr,//featureLevels,
        0,
        D3D11_SDK_VERSION,
        &scd,
        m_swapChain.GetAddressOf(),
        m_device.GetAddressOf(),
        nullptr,//&featureLevel,
        m_context.GetAddressOf()
    );

    ID3D11Resource* pBackBuffer = nullptr;
    m_swapChain->GetBuffer(0, __uuidof(ID3D11Resource), (void**)&pBackBuffer); // Récupère le buffer de rendu arrière du swap chain
    if (m_device != nullptr) {
        m_device->CreateRenderTargetView(pBackBuffer, nullptr, &m_renderTargetView); // Crée une vue de rendu à partir du buffer de rendu arrière
    }
    pBackBuffer->Release(); // Libère le buffer de rendu arrière, car il n'est plus nécessaire après la création de la vue de rendu

    

    if (FAILED(hr)) {
        // Astuce pro : Si ça échoue, c'est souvent parce que l'ordi n'a pas DX11 complet
        // ou que le SDK Debug n'est pas installé.
        MessageBox(nullptr, L"Echec de l'init.", L"Erreur DirectX", MB_ICONERROR);
        return -1;
        //return hr;
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

IDXGIAdapter1* Renderer::searchForAdapters() {
    IDXGIFactory1* pFactory = nullptr; // Pointeur pour la factory DXGI
    CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&pFactory); // On créé une instance de la factory DXGI pour pouvoir énumérer les adaptateurs disponibles

    IDXGIAdapter1* pAdapter = nullptr;
    IDXGIAdapter1* bestAdapter = nullptr;
    SIZE_T maxVRam = 0;

    for (UINT i = 0; pFactory->EnumAdapters1(i, &pAdapter) != DXGI_ERROR_NOT_FOUND; ++i) {
        DXGI_ADAPTER_DESC1 desc;
        pAdapter->GetDesc1(&desc);
        if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
            continue; // Ignore les adaptateurs logiciels
        if (desc.DedicatedVideoMemory > maxVRam) {
            maxVRam = desc.DedicatedVideoMemory;
            bestAdapter = pAdapter; // Met à jour le meilleur adaptateur trouvé jusqu'à présent
        }
    }
    return bestAdapter;
}