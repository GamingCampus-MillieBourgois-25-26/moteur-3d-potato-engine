#pragma once
template<typename T>
class ConstantBuffer {
public:
    ConstantBuffer() = default;

    HRESULT Initialize(ComPtr<ID3D11Device> device) {
        static_assert((sizeof(T) % 16) == 0, "Constant Buffer struct must be 16-byte aligned");

        D3D11_BUFFER_DESC cbd = {};
        cbd.Usage = D3D11_USAGE_DYNAMIC;        // Accès fréquent CPU
        cbd.ByteWidth = static_cast<UINT>(sizeof(T));
        cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; // Nécessaire pour Map/Unmap
        cbd.MiscFlags = 0;
        cbd.StructureByteStride = 0;

        return device->CreateBuffer(&cbd, nullptr, m_buffer.GetAddressOf());
    }

    void Update(ComPtr<ID3D11DeviceContext> context, const T& data) {
        if (!m_buffer) return; // Sécurité si Initialize a échoué

        D3D11_MAPPED_SUBRESOURCE mappedResource;
        // Map verrouille le buffer pour l'écriture CPU
        if (SUCCEEDED(context->Map(m_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource))) {
            memcpy(mappedResource.pData, &data, sizeof(T));
            context->Unmap(m_buffer.Get(), 0);
        }
    }

    ID3D11Buffer* Get() const { return m_buffer.Get(); }
    // Adresse pour faciliter l'utilisation dans les fonctions prenant ID3D11Buffer**
    ID3D11Buffer* const* GetAddressOf() const { return m_buffer.GetAddressOf(); }

private:
    ComPtr<ID3D11Buffer> m_buffer;
};