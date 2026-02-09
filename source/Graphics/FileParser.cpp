#include "FileParser.h"

const void FileParser::StartPars()
{





	std::fstream* fs;
	fs->open("file");
	
	char currentChar;
	while(fs->get(currentChar))
	{
		switch(currentChar)
		{
		case 'v':
			std::cout << "Caca" << '\n';
			break;
		}
	}

	fs->close();
}

std::unique_ptr<std::vector<std::filesystem::path>> FileParser::GetExtensionsFile(std::string* extension)
{
	std::filesystem::path folder = "C:\Users\poiss\source\repos\GamingCampus-MillieBourgois-25-26\moteur-3d-potato-engine";
	std::unique_ptr<std::vector<std::filesystem::path>> file;

	for (const auto& entry : std::filesystem::recursive_directory_iterator(folder))
	{
		if (entry.is_regular_file() && entry.path().extension() == *extension)
		{
			file->push_back(entry.path());
			OutputDebugStringA("CACA");
		}
	}

	return file;
}
