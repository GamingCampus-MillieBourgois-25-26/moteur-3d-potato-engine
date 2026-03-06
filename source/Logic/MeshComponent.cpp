#include "Logic/MeshComponent.h"

void MeshComponent::SetMesh(std::shared_ptr<Mesh> meshPtr) { mesh = meshPtr; }

std::shared_ptr<Mesh> MeshComponent::GetMesh() { return mesh; }

ID3D11VertexShader* MeshComponent::GetVertexShader()
{
	return vs;
}
ID3D11PixelShader* MeshComponent::GetPixelShader()
{
	return ps;
}

DirectX::XMMATRIX MeshComponent::GetWorldMatrix()
{
	return worldMatrix;
}
DirectX::XMFLOAT4 MeshComponent::GetColor()
{
	return color;
}

void MeshComponent::SetVertexShader(ID3D11VertexShader* shader) { vs = shader; }
void MeshComponent::SetPixelShader(ID3D11PixelShader* shader) { ps = shader; }

void MeshComponent::SetColor(const DirectX::XMFLOAT4& c)
{
	for (auto& v : mesh->vertices)
	{
		v.color = c;
	}
}