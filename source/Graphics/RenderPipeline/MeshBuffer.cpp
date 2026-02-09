#include <../include/Graphics/RenderPipeline/MeshBuffer.h>

    HRESULT MeshBuffer::Initialize(ComPtr<ID3D11Device> device, const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices) {
        HRESULT hr;

        // 1. Vertex Buffer
        D3D11_BUFFER_DESC vbd = {};
        vbd.Usage = D3D11_USAGE_IMMUTABLE; // Optimisation GPU : lecture seule
        vbd.ByteWidth = static_cast<UINT>(sizeof(Vertex) * vertices.size());
        vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        vbd.CPUAccessFlags = 0;

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

        m_indexCount = static_cast<UINT>(indices.size());
        return hr;
    }

    void MeshBuffer::Bind(ComPtr<ID3D11DeviceContext> context) {
        UINT stride = sizeof(Vertex);
        UINT offset = 0;
        context->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);
        context->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
    }
