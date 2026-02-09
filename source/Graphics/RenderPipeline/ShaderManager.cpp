#include <../Include/Graphics/RenderPipeline/ShaderManager.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3dcompiler.lib")

// 1. Méthode générique de compilation (Privée)
HRESULT ShaderManager::CompileShader(const std::wstring& filename, const char* entryPoint, const char* profile, ComPtr<ID3DBlob>& shaderBlob) {
    ComPtr<ID3DBlob> errorBlob;
    UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
    flags |= D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

    HRESULT hr = D3DCompileFromFile(
        filename.c_str(),
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        entryPoint,
        profile,
        flags, 0,
        &shaderBlob,
        &errorBlob
    );

    if (FAILED(hr)) {
        if (errorBlob) {
            OutputDebugStringA((char*)errorBlob->GetBufferPointer());
        }
        return hr;
    }
    return S_OK;
}

// 2. Création du Vertex Shader (Crucial : renvoie le blob)
HRESULT ShaderManager::CreateVertexShader(ComPtr<ID3D11Device> device, const std::wstring& filename, ComPtr<ID3D11VertexShader>& vertexShader, ComPtr<ID3DBlob>& shaderBlob) {
    // On compile d'abord
    HRESULT hr = CompileShader(filename, "main", "vs_5_0", shaderBlob);
    if (FAILED(hr)) return hr;

    // On crée l'objet shader
    return device->CreateVertexShader(
        shaderBlob->GetBufferPointer(),
        shaderBlob->GetBufferSize(),
        nullptr,
        vertexShader.GetAddressOf()
    );
}

// 3. Création du Pixel Shader
HRESULT ShaderManager::CreatePixelShader(ComPtr<ID3D11Device> device, const std::wstring& filename, ComPtr<ID3D11PixelShader>& pixelShader) {
    ComPtr<ID3DBlob> shaderBlob;
    HRESULT hr = CompileShader(filename, "main", "ps_5_0", shaderBlob);
    if (FAILED(hr)) return hr;

    return device->CreatePixelShader(
        shaderBlob->GetBufferPointer(),
        shaderBlob->GetBufferSize(),
        nullptr,
        pixelShader.GetAddressOf()
    );
}