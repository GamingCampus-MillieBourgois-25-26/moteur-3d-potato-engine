#include "Camera.h"
#include <windows.h>
#include <algorithm>

Camera::Camera() :
    m_position(0.0f, 1.0f, -5.0f),
    m_yaw(0.0f),
    m_pitch(0.0f),
    m_moveSpeed(10.0f),
    m_lookSensitivity(0.15f)
{
    UpdateCameraVectors();
}

void Camera::UpdateCameraVectors() {
    float rPitch = DirectX::XMConvertToRadians(m_pitch);
    float rYaw = DirectX::XMConvertToRadians(m_yaw);

    DirectX::XMVECTOR forward = DirectX::XMVectorSet(
        cos(rPitch) * sin(rYaw),
        sin(rPitch),
        cos(rPitch) * cos(rYaw),
        0.0f
    );
    DirectX::XMStoreFloat3(&m_forward, DirectX::XMVector3Normalize(forward));

    DirectX::XMVECTOR worldUp = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    DirectX::XMVECTOR forwardVec = DirectX::XMLoadFloat3(&m_forward);
    DirectX::XMVECTOR right = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(worldUp, forwardVec));
    DirectX::XMVECTOR up = DirectX::XMVector3Cross(forwardVec, right);

    DirectX::XMStoreFloat3(&m_right, right);
    DirectX::XMStoreFloat3(&m_up, up);
}

void Camera::Update(float deltaTime, bool isRightClickPressed, float mouseDx, float mouseDy) {
    if (isRightClickPressed) {
        m_yaw += mouseDx * m_lookSensitivity;
        m_pitch -= mouseDy * m_lookSensitivity;
        m_pitch = std::clamp(m_pitch, -89.0f, 89.0f);
        UpdateCameraVectors();
    }

    DirectX::XMVECTOR pos = DirectX::XMLoadFloat3(&m_position);
    DirectX::XMVECTOR fwd = DirectX::XMLoadFloat3(&m_forward);
    DirectX::XMVECTOR rgt = DirectX::XMLoadFloat3(&m_right);
    float speed = m_moveSpeed * deltaTime;

    DirectX::XMVECTOR s = DirectX::XMVectorReplicate(speed);

    if (GetAsyncKeyState('Z') & 0x8000) pos = DirectX::XMVectorMultiplyAdd(fwd, s, pos);
    if (GetAsyncKeyState('S') & 0x8000) pos = DirectX::XMVectorMultiplyAdd(fwd, DirectX::XMVectorNegate(s), pos);
    if (GetAsyncKeyState('D') & 0x8000) pos = DirectX::XMVectorMultiplyAdd(rgt, s, pos);
    if (GetAsyncKeyState('Q') & 0x8000) pos = DirectX::XMVectorMultiplyAdd(rgt, DirectX::XMVectorNegate(s), pos);

    if (GetAsyncKeyState(VK_SPACE) & 0x8000) pos = DirectX::XMVectorAdd(pos, DirectX::XMVectorScale(DirectX::XMVectorSet(0, 1, 0, 0), speed));
    if (GetAsyncKeyState(VK_SHIFT) & 0x8000) pos = DirectX::XMVectorSubtract(pos, DirectX::XMVectorScale(DirectX::XMVectorSet(0, 1, 0, 0), speed));

    DirectX::XMStoreFloat3(&m_position, pos);
}

// --- CETTE FONCTION MANQUAIT DANS TON PRÉCÉDENT MESSAGE ---
DirectX::XMMATRIX Camera::GetViewMatrix() const {
    DirectX::XMVECTOR pos = DirectX::XMLoadFloat3(&m_position);
    DirectX::XMVECTOR fwd = DirectX::XMLoadFloat3(&m_forward);
    DirectX::XMVECTOR up = DirectX::XMLoadFloat3(&m_up);
    return DirectX::XMMatrixLookToLH(pos, fwd, up);
}