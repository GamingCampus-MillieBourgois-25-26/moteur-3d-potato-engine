#include "Graphics/RenderPipeline/MeshBuffer.h"

HRESULT MeshBuffer::Initialize(Microsoft::WRL::ComPtr<ID3D11Device> device, const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices) {
    if (vertices.empty() || indices.empty()) return E_INVALIDARG;

    HRESULT hr;

    // 1. Vertex Buffer
    D3D11_BUFFER_DESC vbd = {};
    vbd.Usage = D3D11_USAGE_IMMUTABLE;
    vbd.ByteWidth = static_cast<UINT>(sizeof(Vertex) * vertices.size());
    vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA vinitData = {};
    vinitData.pSysMem = vertices.data();
    hr = device->CreateBuffer(&vbd, &vinitData, m_vertexBuffer.GetAddressOf());
    if (FAILED(hr)) return hr;

    // 2. Index Buffer
    D3D11_BUFFER_DESC ibd = {};
    ibd.Usage = D3D11_USAGE_IMMUTABLE;
    ibd.ByteWidth = static_cast<UINT>(sizeof(uint32_t) * indices.size());
    ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;

    D3D11_SUBRESOURCE_DATA iinitData = {};
    iinitData.pSysMem = indices.data();
    hr = device->CreateBuffer(&ibd, &iinitData, m_indexBuffer.GetAddressOf());
    if (FAILED(hr)) return hr;

    m_indexCount = static_cast<UINT>(indices.size());
    return S_OK;
}

void MeshBuffer::Bind(Microsoft::WRL::ComPtr<ID3D11DeviceContext> context) {
    UINT stride = sizeof(Vertex);
    UINT offset = 0;

    // On bind l'Input Layout
    if (m_inputLayout) {
        context->IASetInputLayout(m_inputLayout.Get());
    }

    context->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);
    context->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

HRESULT MeshBuffer::CreateInputLayout(Microsoft::WRL::ComPtr<ID3D11Device> device, const void* shaderBytecode, size_t bytecodeLength) {
    D3D11_INPUT_ELEMENT_DESC layoutDesc[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };


    return device->CreateInputLayout(
        layoutDesc,
        ARRAYSIZE(layoutDesc),
        shaderBytecode,
        bytecodeLength,
        m_inputLayout.GetAddressOf() // On stocke le résultat dans le membre de classe
    );
}