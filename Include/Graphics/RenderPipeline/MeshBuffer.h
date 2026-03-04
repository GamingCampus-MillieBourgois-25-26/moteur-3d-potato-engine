#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <vector>
#include "Vertex.h" // On utilise le fichier Types.h validé ensemble

class MeshBuffer {
public:
    MeshBuffer() = default;

    HRESULT Initialize(Microsoft::WRL::ComPtr<ID3D11Device> device,
        const std::vector<Vertex>& vertices,
        const std::vector<uint32_t>& indices);

    void Bind(Microsoft::WRL::ComPtr<ID3D11DeviceContext> context);


    UINT GetIndexCount() const { return m_indexCount; }

private:
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_indexBuffer;
    Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout; // INDISPENSABLE
    UINT m_indexCount = 0;
};