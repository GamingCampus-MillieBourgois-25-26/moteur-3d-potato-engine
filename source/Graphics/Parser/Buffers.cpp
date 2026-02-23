#include "../include/Graphics/Buffers.h"

void Buffers::AddMeshBuffers(std::shared_ptr<Mesh> mesh, std::string meshname)
{
	meshBuffer.emplace(meshname,mesh);
}

Buffers* Buffers::getInstance()
{
	if (instance == nullptr)
		instance = new Buffers();
	return instance;
}

Buffers* Buffers::instance = nullptr;
Buffers* buffer = Buffers::getInstance();