#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <string>
#include <d3dcompiler.h>

using Microsoft::WRL::ComPtr;

class ShaderManager {
public:
    // Charge et crée un Vertex Shader + renvoie le bytecode pour l'Input Layout
    static HRESULT CreateVertexShader(
        ComPtr<ID3D11Device> device,
        const std::wstring& filename,
        ComPtr<ID3D11VertexShader>& vs,
        ComPtr<ID3DBlob>& shaderBlob // Nécessaire pour l'Input Layout !
    );

    // Charge et crée un Pixel Shader
    static HRESULT CreatePixelShader(
        ComPtr<ID3D11Device> device,
        const std::wstring& filename,
        ComPtr<ID3D11PixelShader>& ps
    );

private:
    static HRESULT CompileShader(
        const std::wstring& filename,
        const char* entryPoint,
        const char* profile,
        ComPtr<ID3DBlob>& shaderBlob
    );
};

