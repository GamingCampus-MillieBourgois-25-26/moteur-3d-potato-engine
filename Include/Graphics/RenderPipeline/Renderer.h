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
#include "Logic/MeshComponent.h"

class Renderer {
public:
    Renderer() = default;
    ~Renderer() = default;

    // Initialisation principale
    HRESULT Initialize(HWND hwnd, int width, int height);

    // Boucle de rendu
    void RenderFrame(const PerFrameCB& frameData, std::vector<MeshComponent>& items);

    
    Microsoft::WRL::ComPtr<ID3D11Device> GetDevice() const { return m_device; }


    // Ajout pour merge ImGui  Dans render.h, sous GetDevice()
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> GetContext() const { return m_context; }

    void Present() { m_swapChain->Present(1, 0); }

    //la scene dans ImGui
    // Pour que ImGui puisse récupérer la texture de la scène
    ID3D11ShaderResourceView* GetSceneSRV() const { return m_sceneSRV.Get(); }

    // À appeler lors du redimensionnement de la fenêtre ImGui si nécessaire
    HRESULT CreateSceneResources(int width, int height);

    
    ID3D11RenderTargetView* const* GetMainRTVAddress() const { return m_renderTargetView.GetAddressOf(); }
    

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

    //la scene dans ImGui
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_sceneRTV;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_sceneSRV; // La vue pour ImGui

    // Pour plus tard (déjà prêt)
    ConstantBuffer<PerFrameCB>         m_perFrameCB;
    ConstantBuffer<PerObjectCB>        m_perObjectCB;
};


