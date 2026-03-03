#pragma once
#include "stb_image/stb_image.h"
#include <string>
#include <d3d11.h>

class Texture
{
public:
    Texture() = default;
    ~Texture();

    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    Texture(Texture&& other) noexcept;
    Texture& operator=(Texture&& other) noexcept;

    bool Load(ID3D11Device* device, const std::string& path);

    void Bind(ID3D11DeviceContext* context, UINT slot = 0) const;

    ID3D11ShaderResourceView* GetSRV() const { return m_SRV; }

    int GetWidth() const { return m_Width; }
    int GetHeight() const { return m_Height; }

private:
    void Release();

private:
    ID3D11ShaderResourceView* m_SRV = nullptr;

    int m_Width = 0;
    int m_Height = 0;
};