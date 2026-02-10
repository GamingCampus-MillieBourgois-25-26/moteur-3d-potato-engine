#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <vector>
#include "Vertex.h"
#include "MeshBuffer.h"
#include "ConstantBuffer.h"
#include "ShaderManager.h"

class Renderer {
public:
    Renderer() = default;
    ~Renderer() = default;

    // Initialisation principale
    HRESULT Initialize(HWND hwnd, int width, int height);

    // Boucle de rendu
    void RenderFrame();

    // Nettoyage (facultatif avec ComPtr, mais propre pour le groupe)
    //void Shutdown();

private:
    // Méthodes d'initialisation internes
    HRESULT CreateDeviceAndSwapChain(HWND hwnd, int width, int height);
    HRESULT CreateMainViews(int width, int height);
    HRESULT SetupTestTriangle(); // Ta méthode de test

    // Core DX11
    Microsoft::WRL::ComPtr<ID3D11Device>           m_device;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext>    m_context;
    Microsoft::WRL::ComPtr<IDXGISwapChain>         m_swapChain;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetView;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthStencilView;
    Microsoft::WRL::ComPtr<ID3D11RasterizerState>  m_rasterizerState;

    // Ressources pour le test du triangle
    MeshBuffer                         m_testMesh;
    Microsoft::WRL::ComPtr<ID3D11VertexShader> m_testVS;
    Microsoft::WRL::ComPtr<ID3D11PixelShader>  m_testPS;

    // Pour plus tard (déjà prêt)
    ConstantBuffer<PerFrameCB>         m_perFrameCB;
};