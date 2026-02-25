#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <string>
#include <d3dcompiler.h>

// On retire le "using", on utilise le nom complet dans les signatures
class ShaderManager {
public:
    static HRESULT CreateVertexShader(
        Microsoft::WRL::ComPtr<ID3D11Device> device,
        const std::wstring& filename,
        Microsoft::WRL::ComPtr<ID3D11VertexShader>& vs,
        Microsoft::WRL::ComPtr<ID3DBlob>& shaderBlob
    );

    static HRESULT CreatePixelShader(
        Microsoft::WRL::ComPtr<ID3D11Device> device,
        const std::wstring& filename,
        Microsoft::WRL::ComPtr<ID3D11PixelShader>& ps
    );

private:
    static HRESULT CompileShader(
        const std::wstring& filename,
        const char* entryPoint,
        const char* profile,
        Microsoft::WRL::ComPtr<ID3DBlob>& shaderBlob
    );
};