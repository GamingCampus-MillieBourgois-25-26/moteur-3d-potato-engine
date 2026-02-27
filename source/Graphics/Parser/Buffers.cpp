#include "../include/Graphics/Buffers.h"

void Buffers::AddMeshBuffers(std::shared_ptr<Mesh> mesh, std::string meshname)
{
	meshBuffer.emplace(meshname,mesh);
}

std::shared_ptr<Mesh> Buffers::GetMesh(const std::string& meshname)
{
	auto mesh = meshBuffer.find(meshname);
	if(mesh != meshBuffer.end())
	{
		return mesh->second;
	}
	return nullptr;
}