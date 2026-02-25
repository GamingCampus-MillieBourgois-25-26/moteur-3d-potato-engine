#pragma once
#include "Mesh.h"
#include "unordered_map"

class Buffers
{
private:
	static Buffers* instance;
	std::unordered_map<std::string, std::shared_ptr<Mesh>> meshBuffer;
public:

	void AddMeshBuffers(std::shared_ptr<Mesh>,std::string);
	std::shared_ptr<Mesh> GetMesh(const std::string&);
	static Buffers* getInstance();
};

extern Buffers* buffer;