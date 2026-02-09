#include "../Include/Graphics/FileParser.h"

const void FileParser::StartPars()
{
	std::vector<std::filesystem::path> allFile;
	allFile = GetExtensionsFile(".obj");

	while(!allFile.empty())
	{
		std::fstream fs(allFile[0]);
		if (!fs.is_open())
			throw std::runtime_error("Impossible d'ouvrir le fichier");

		std::string line;
		while (std::getline(fs,line))
		{
			if (line.empty() || line[0] == '#') continue;

			auto mesh = std::make_shared<Mesh>();
			std::istringstream iss(line);
			std::string prefix;
			iss >> prefix;

			if(prefix == "v")
			{
				float x, y, z;
				iss >> x >> y >> z;
				auto vertices = std::make_shared<Vertex>();
				vertices->position = {x,y,z};
				std::cout << "X : " << x <<'\n';
				std::cout << "Y : " << y <<'\n';
				std::cout << "Z : " << z <<'\n';
				std::cout << '\n';
			}


		}
		allFile.erase(allFile.begin());
		fs.close();
	}
}

std::vector<std::filesystem::path> FileParser::GetExtensionsFile(std::string extension)
{
	std::filesystem::path folder = "assets";
	std::vector<std::filesystem::path> file;

	for (const auto& entry : std::filesystem::recursive_directory_iterator(folder))
	{
		if (entry.is_regular_file() && entry.path().extension() == extension)
			file.push_back(entry.path());
	}

	return file;
}
