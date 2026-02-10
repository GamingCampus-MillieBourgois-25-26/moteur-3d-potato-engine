#include "Graphics/RenderPipeline/ShaderManager.h" // Utilisez des chemins propres via l'IDE

#pragma comment(lib, "d3dcompiler.lib")

using namespace Microsoft::WRL; // Autorisé ici car on est dans le .cpp

HRESULT ShaderManager::CompileShader(const std::wstring& filename, const char* entryPoint, const char* profile, ComPtr<ID3DBlob>& shaderBlob) {
    ComPtr<ID3DBlob> errorBlob;
    UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
    flags |= D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

    // D3D_COMPILE_STANDARD_FILE_INCLUDE permet d'utiliser #include dans les fichiers HLSL
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
            // Affiche l'erreur HLSL précise dans la fenêtre "Sortie" de Visual Studio
            OutputDebugStringA(static_cast<const char*>(errorBlob->GetBufferPointer()));
        }
        return hr;
    }
    return S_OK;
}

HRESULT ShaderManager::CreateVertexShader(ComPtr<ID3D11Device> device, const std::wstring& filename, ComPtr<ID3D11VertexShader>& vertexShader, ComPtr<ID3DBlob>& shaderBlob) {
    HRESULT hr = CompileShader(filename, "main", "vs_5_0", shaderBlob);
    if (FAILED(hr)) return hr;

    return device->CreateVertexShader(
        shaderBlob->GetBufferPointer(),
        shaderBlob->GetBufferSize(),
        nullptr,
        vertexShader.GetAddressOf()
    );
}

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