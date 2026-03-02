#include "../include/Logic/MeshComponent.h"

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