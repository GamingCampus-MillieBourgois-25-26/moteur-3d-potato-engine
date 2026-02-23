#include <iostream>
#include <memory>
#include <fstream>
#include <vector>
#include <filesystem>
#include <windows.h>
#include <DirectXMath.h>
#include "Buffers.h"

class FileParser
{
public:

	FileParser()
	{
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
	}
	const void StartPars();

	std::vector<std::filesystem::path> GetExtensionsFile(std::string extension);
private:
};