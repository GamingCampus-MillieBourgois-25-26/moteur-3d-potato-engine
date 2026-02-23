#pragma once
#include <d3d11.h>
#include <d3d11_1.h>
#include <dxgi.h>
#include <wrl/client.h>
#include <vector>
#include "Vertex.h"
#include "MeshBuffer.h"
#include "ConstantBuffer.h"
#include "ShaderManager.h"


struct RenderItem {
    MeshBuffer* mesh;
    ID3D11VertexShader* vs;
    ID3D11PixelShader* ps;
    DirectX::XMMATRIX worldMatrix;
    DirectX::XMFLOAT4 color;
};

class Renderer {
public:
    Renderer() = default;
    ~Renderer() = default;

    // Initialisation principale
    HRESULT Initialize(HWND hwnd, int width, int height);

    // Boucle de rendu
    void RenderFrame(const PerFrameCB& frameData, const std::vector<RenderItem>& items);

    
    Microsoft::WRL::ComPtr<ID3D11Device> GetDevice() const { return m_device; }


    // Ajout pour merge ImGui  Dans render.h, sous GetDevice()
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> GetContext() const { return m_context; }

    void Present() { m_swapChain->Present(1, 0); }

private:
    // Méthodes d'initialisation internes
    HRESULT CreateDeviceAndSwapChain(HWND hwnd, int width, int height);
    HRESULT CreateMainViews(int width, int height);

    IDXGIAdapter1* searchForAdapters();

    // Core DX11
    Microsoft::WRL::ComPtr<ID3D11Device>           m_device;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext>    m_context;
    Microsoft::WRL::ComPtr<IDXGISwapChain>         m_swapChain;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetView;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthStencilView;
    Microsoft::WRL::ComPtr<ID3D11RasterizerState>  m_rasterizerState;

    // Pour plus tard (déjà prêt)
    ConstantBuffer<PerFrameCB>         m_perFrameCB;
    ConstantBuffer<PerObjectCB>        m_perObjectCB;
};


