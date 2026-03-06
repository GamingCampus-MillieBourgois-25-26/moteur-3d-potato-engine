#pragma once

#include "Component.h"
#include "Graphics/Mesh.h"
#include <memory>
#include <string>

enum class COLOR
{
	RED,
	BLUE,
	GREEN,
	YELLOW,
	ORANGE
};

class MeshComponent : public Component
{
public:
	MeshComponent()
		: vs(nullptr)
		, ps(nullptr)
		, worldMatrix(DirectX::XMMatrixIdentity())
		, color({ 1.0f, 1.0f, 1.0f, 1.0f })
	{}

	void SetMesh(std::shared_ptr<Mesh>);

	std::shared_ptr<Mesh> GetMesh();
	ID3D11VertexShader* GetVertexShader();
	ID3D11PixelShader* GetPixelShader();
	DirectX::XMMATRIX GetWorldMatrix();
	DirectX::XMFLOAT4 GetColor();

	void SetVertexShader(ID3D11VertexShader* shader);

	void SetPixelShader(ID3D11PixelShader* shader);
	void SetWorldMatrix(const DirectX::XMMATRIX& mat) { worldMatrix = mat; }
	void SetColor(const DirectX::XMFLOAT4& c);

private:
	std::shared_ptr<Mesh> mesh;
	ID3D11VertexShader* vs;
	ID3D11PixelShader* ps;
	DirectX::XMMATRIX worldMatrix;
	DirectX::XMFLOAT4 color;
};