#pragma once
#include <vector>
#include "Component.h"
#include "Math/Vector3.h"
#include "Math/Matrix4.h"

struct TransformComponent : public Component
{
    Vector3 localPosition{ 0,0,0 };
    Vector3 localRotation{ 0,0,0 };  // Euler (rad)
    Vector3 localScale{ 1,1,1 };

    Matrix4 localMatrix;
    Matrix4 worldMatrix;

    TransformComponent* parent = nullptr;
    std::vector<TransformComponent*> children;

    bool dirty = true;

    void SetParent(TransformComponent* newParent);
    void MarkDirty();
    void UpdateMatrices();

    const Matrix4& GetWorldMatrix();
};
