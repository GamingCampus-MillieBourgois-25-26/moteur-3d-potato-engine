#include "Texture/Material.h"

void Material::SetTexture(std::shared_ptr<Texture> texture)
{
    m_Texture = texture;
}

void Material::Bind(ID3D11DeviceContext* context)
{
    if (m_Texture)
        m_Texture->Bind(context, 0);

    if (m_Sampler)
        context->PSSetSamplers(0, 1, &m_Sampler);
}