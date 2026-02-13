#pragma once
#include <d3d11.h>
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

private:
    // Méthodes d'initialisation internes
    HRESULT CreateDeviceAndSwapChain(HWND hwnd, int width, int height);
    HRESULT CreateMainViews(int width, int height);

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
