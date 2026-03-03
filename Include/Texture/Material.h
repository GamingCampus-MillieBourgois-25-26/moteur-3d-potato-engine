#pragma once

#include <memory>
#include <d3d11.h>
#include "Texture/Texture.h"

class Material
{
public:
    Material() = default;

    void SetTexture(std::shared_ptr<Texture> texture);
    void Bind(ID3D11DeviceContext* context);

private:
    std::shared_ptr<Texture> m_Texture;
    ID3D11SamplerState* m_Sampler = nullptr;
};