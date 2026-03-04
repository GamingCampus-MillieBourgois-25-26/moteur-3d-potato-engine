#pragma once
#include <DirectXMath.h>

class Camera {
public:
    Camera();

    // Récupérer la matrice de vue
    DirectX::XMMATRIX GetViewMatrix() const;

    // Fonction principale de mise à jour
    void Update(float deltaTime, bool isRightClickPressed, float mouseDx, float mouseDy);

    // Getters / Setters
    DirectX::XMFLOAT3 GetPosition() const { return m_position; }
    void SetPosition(float x, float y, float z) { m_position = { x, y, z }; }

private:
    DirectX::XMFLOAT3 m_position;
    DirectX::XMFLOAT3 m_forward;
    DirectX::XMFLOAT3 m_up;
    DirectX::XMFLOAT3 m_right;

    float m_yaw;   // Rotation horizontale
    float m_pitch; // Rotation verticale

    float m_moveSpeed;
    float m_lookSensitivity;

    void UpdateCameraVectors();
};