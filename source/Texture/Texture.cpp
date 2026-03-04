#include "Texture/Texture.h"
#include <iostream>


Texture::~Texture()
{
    Release();
}

Texture::Texture(Texture&& other) noexcept
{
    m_SRV = other.m_SRV;
    m_Width = other.m_Width;
    m_Height = other.m_Height;

    other.m_SRV = nullptr;
}

Texture& Texture::operator=(Texture&& other) noexcept
{
    if (this != &other)
    {
        Release();

        m_SRV = other.m_SRV;
        m_Width = other.m_Width;
        m_Height = other.m_Height;

        other.m_SRV = nullptr;
    }
    return *this;
}

void Texture::Release()
{
    if (m_SRV)
    {
        m_SRV->Release();
        m_SRV = nullptr;
    }
}

bool Texture::Load(ID3D11Device* device, const std::string& path)
{
    Release();

    int width, height, channels;

    stbi_set_flip_vertically_on_load(true);

    unsigned char* data = stbi_load(
        path.c_str(),
        &width,
        &height,
        &channels,
        STBI_rgb_alpha // force RGBA
    );

    if (!data)
    {
        std::cout << "Failed to load texture: " << path << std::endl;
        return false;
    }

    m_Width = width;
    m_Height = height;

    D3D11_TEXTURE2D_DESC desc = {};
    desc.Width = width;
    desc.Height = height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = data;
    initData.SysMemPitch = width * 4;

    ID3D11Texture2D* texture = nullptr;

    HRESULT hr = device->CreateTexture2D(&desc, &initData, &texture);
    if (FAILED(hr))
    {
        std::cout << "Failed to create Texture2D." << std::endl;
        stbi_image_free(data);
        return false;
    }

    hr = device->CreateShaderResourceView(texture, nullptr, &m_SRV);
    texture->Release();

    stbi_image_free(data);

    if (FAILED(hr))
    {
        std::cout << "Failed to create ShaderResourceView." << std::endl;
        return false;
    }

    return true;
}

void Texture::Bind(ID3D11DeviceContext* context, UINT slot) const
{
    context->PSSetShaderResources(slot, 1, &m_SRV);
}