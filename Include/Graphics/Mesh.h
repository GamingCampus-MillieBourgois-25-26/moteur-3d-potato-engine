#pragma once

#include "Vertex.h"
#include <vector>
#include <memory>
#include <string>

class Mesh 
{
public:
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
};