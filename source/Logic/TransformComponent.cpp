#include "Logic/TransformComponent.h"

void TransformComponent::SetParent(TransformComponent* newParent)
{
    if (parent)
    {
        auto& siblings = parent->children;
        siblings.erase(std::remove(siblings.begin(), siblings.end(), this), siblings.end());
    }

    parent = newParent;

    if (parent)
        parent->children.push_back(this);

    MarkDirty();
}

void TransformComponent::MarkDirty()
{
    dirty = true;
    for (auto child : children)
        child->MarkDirty();
}

const DirectX::XMMATRIX& TransformComponent::GetWorldMatrix()
{
    if (dirty)
        UpdateMatrices();

    return worldMatrix;
}

void TransformComponent::UpdateMatrices() {
    DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(localPosition.x, localPosition.y, localPosition.z);

    // Correction ici : RollPitchYaw pour XMFLOAT3 (Angles d'Euler)
    DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(
        DirectX::XMConvertToRadians(localRotation.x),
        DirectX::XMConvertToRadians(localRotation.y),
        DirectX::XMConvertToRadians(localRotation.z)
    );

    DirectX::XMMATRIX S = DirectX::XMMatrixScaling(localScale.x, localScale.y, localScale.z);

    localMatrix = S * R * T;

    if (parent) {
        // Attention : récursion ici. Si la hiérarchie est de 1000 objets, risque de Stack Overflow.
        worldMatrix = localMatrix * parent->GetWorldMatrix();
    }
    else {
        worldMatrix = localMatrix;
    }

    dirty = false;
}
