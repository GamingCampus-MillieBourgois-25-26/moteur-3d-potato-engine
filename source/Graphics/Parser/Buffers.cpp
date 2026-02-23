#include "../include/Graphics/Buffers.h"

void Buffers::AddMeshBuffers(std::shared_ptr<Mesh> mesh)
{
	meshBuffer.insert();
}

Buffers* Buffers::getInstance()
{
	if (instance == nullptr)
		instance = new Buffers();
	return instance;
}

Buffers* Buffers::instance = nullptr;
Buffers* buffer = Buffers::getInstance();