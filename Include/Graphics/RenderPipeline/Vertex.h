#pragma once
#include <d3d11.h>
#include <wrl/client.h> // Pour Microsoft::WRL::ComPtr
#include <vector>
#include <DirectXMath.h>

using Microsoft::WRL::ComPtr;

// Structure de sommet (Input Layout)
struct Vertex {
    DirectX::XMFLOAT3 position; // 12 octets
    DirectX::XMFLOAT3 normal;   // 12 octets
    DirectX::XMFLOAT2 texCoord; // 8 octets
	DirectX::XMFLOAT4 color;    // 16 octets (RGBA)
    // Total : 32 octets (Bien aligné, multiple de 4 et 8)
};

// Structure pour la caméra (Slot 0)
struct alignas(16) PerFrameCB {
    DirectX::XMMATRIX viewMatrix;       // 64 octets
    DirectX::XMMATRIX projectionMatrix; // 64 octets
};

// Structure pour l'objet (Slot 1)
struct alignas(16) PerObjectCB {
    DirectX::XMMATRIX worldMatrix;      // 64 octets
    DirectX::XMFLOAT4 meshColor;        // 16 octets
    // Ajout d'un padding explicite si tu ajoutes d'autres variables plus tard
    // pour toujours atteindre un multiple de 16 octets au total.
};

