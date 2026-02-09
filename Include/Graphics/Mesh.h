#pragma once

#include "Vertex.h"
#include <vector>
#include <memory>

class Mesh 
{
public:
	std::shared_ptr<std::vector<Vertex>> vertices;
	std::shared_ptr<uint32_t> indices;
};