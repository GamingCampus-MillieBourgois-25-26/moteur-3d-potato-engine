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

const Matrix4& TransformComponent::GetWorldMatrix()
{
    if (dirty)
        UpdateMatrices();

    return worldMatrix;
}

void TransformComponent::UpdateMatrices()
{
    localMatrix = Matrix4::TRS(localPosition, localRotation, localScale);

    if (parent)
        worldMatrix = parent->GetWorldMatrix() * localMatrix;
    else
        worldMatrix = localMatrix;

    dirty = false;
}
