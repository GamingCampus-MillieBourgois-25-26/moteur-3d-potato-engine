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

private:
	std::shared_ptr<Mesh> mesh;
};