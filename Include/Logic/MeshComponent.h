#pragma once

#include "Component.h"
#include "../include/Graphics/Mesh.h"
#include <memory>
#include <string>

class MeshComponent : public Component
{
public:
	MeshComponent() = default;

	void SetMesh(std::shared_ptr<Mesh>);

	std::shared_ptr<Mesh> GetMesh();
	ID3D11VertexShader* GetVertexShader();
	ID3D11PixelShader* GetPixelShader();
	DirectX::XMMATRIX GetWorldMatrix();
	DirectX::XMFLOAT4 GetColor();

private:
	std::shared_ptr<Mesh> mesh;
	ID3D11VertexShader* vs;
	ID3D11PixelShader* ps;
	DirectX::XMMATRIX worldMatrix;
	DirectX::XMFLOAT4 color;
};