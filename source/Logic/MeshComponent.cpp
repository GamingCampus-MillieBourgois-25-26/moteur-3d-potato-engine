#include "../include/Logic/MeshComponent.h"

void MeshComponent::SetMesh(std::shared_ptr<Mesh> meshPtr) { mesh = meshPtr; }

std::shared_ptr<Mesh> MeshComponent::GetMesh() { return mesh; }
