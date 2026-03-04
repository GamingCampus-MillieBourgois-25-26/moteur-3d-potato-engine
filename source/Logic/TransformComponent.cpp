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

void TransformComponent::UpdateMatrices()
{
    using namespace DirectX;

    // 1. Calcul de la matrice locale (S * R * T)
    XMMATRIX scaling = XMMatrixScaling(localScale.x, localScale.y, localScale.z);

    // Correction : Utilisation de RollPitchYaw si localRotation est un float3 (Euler)
    XMMATRIX rotation = XMMatrixRotationRollPitchYaw(
        XMConvertToRadians(localRotation.x),
        XMConvertToRadians(localRotation.y),
        XMConvertToRadians(localRotation.z)
    );

    XMMATRIX translation = XMMatrixTranslation(localPosition.x, localPosition.y, localPosition.z);

    // Multiplication Row-Major
    localMatrix = scaling * rotation * translation;

    // 2. Calcul de la matrice Monde
    if (parent)
    {
        // On multiplie la matrice locale par celle du parent
        worldMatrix = localMatrix * parent->GetWorldMatrix();
    }
    else
    {
        worldMatrix = localMatrix;
    }

    dirty = false;
}
