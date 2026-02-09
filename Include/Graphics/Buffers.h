#pragma once
#include "Mesh.h"
#include "unordered_map"

class Buffers
{
public:
	std::shared_ptr<std::unordered_map<int,Vertex>> meshBuffer;

};