#include <iostream>
#include <memory>
#include <fstream>
#include <vector>
#include <filesystem>
#include <Windows.h>
#include <DirectXMath.h>

class FileParser
{
public:

	const void StartPars();

	std::unique_ptr<std::vector<std::filesystem::path>> GetExtensionsFile(std::string* extension);
private:
};