#pragma once
#include "Mesh.h"
#include "unordered_map"

class Buffers
{
public:
	std::unordered_map<std::string,std::shared_ptr<Mesh>> meshBuffer;

};