#pragma once // Empêche les inclusions multiples
#include <d3d11.h>
#include <wrl/client.h>
#include <vector>
#include "Vertex.h" // Contient la struct Vertex

class MeshBuffer {
public:
    MeshBuffer() = default;
    HRESULT Initialize(Microsoft::WRL::ComPtr<ID3D11Device> device,
        const std::vector<Vertex>& vertices,
        const std::vector<uint32_t>& indices);
    void Bind(Microsoft::WRL::ComPtr<ID3D11DeviceContext> context);
    void CreateInputLayout(ComPtr<ID3D11Device> device, const std::vector<uint8_t>& vsBytecode);
    UINT GetIndexCount() const { return m_indexCount; }

private:
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_indexBuffer;
    UINT m_indexCount = 0;
};