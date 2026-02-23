#pragma once
#include "Mesh.h"
#include "unordered_map"

class Buffers
{
private:
	static Buffers* instance;

public:
	std::unordered_map<std::string,std::shared_ptr<Mesh>> meshBuffer;

	void AddMeshBuffers(std::shared_ptr<Mesh>);
	static Buffers* getInstance();
};

extern Buffers* buffer;