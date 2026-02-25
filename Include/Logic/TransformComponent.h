#pragma once
#include <vector>
#include "Component.h"
#include <DirectXMath.h>

struct TransformComponent : public Component
{
    DirectX::XMFLOAT3 localPosition{ 0,0,0 };
    DirectX::XMFLOAT3 localRotation{ 0,0,0 };  // Euler (rad)
    DirectX::XMFLOAT3 localScale{ 1,1,1 };

    
    DirectX::XMMATRIX localMatrix;
    DirectX::XMMATRIX worldMatrix;

    TransformComponent* parent = nullptr;
    std::vector<TransformComponent*> children;

    bool dirty = true;

    void SetParent(TransformComponent* newParent);
    void MarkDirty();
    void UpdateMatrices();

    const DirectX::XMMATRIX& GetWorldMatrix();
};
