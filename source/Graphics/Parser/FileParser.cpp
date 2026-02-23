#include "Graphics/FileParser.h"

const void FileParser::StartPars()
{
	std::vector<std::filesystem::path> allFile;
	allFile = GetExtensionsFile(".obj");

	std::vector<DirectX::XMFLOAT3> tempPosition;
	std::vector<DirectX::XMFLOAT3> tempNormales;
	std::vector<DirectX::XMFLOAT2> tempTextures;

	while(!allFile.empty())
	{
		std::fstream fs(allFile[0]);
		if (!fs.is_open())
			throw std::runtime_error("Impossible d'ouvrir le fichier");

		auto mesh = std::make_shared<Mesh>();
		//mesh->name = 
		std::string line;
		while (std::getline(fs,line))
		{
			if (line.empty() || line[0] == '#') continue;

			std::istringstream iss(line);
			std::string prefix;
			iss >> prefix;

			if (prefix == "v")
			{
				float x, y, z;
				iss >> x >> y >> z;
				tempPosition.push_back(DirectX::XMFLOAT3{x,y,z});
			}
			if(prefix == "vt")
			{
				float u, v;
				iss >> u >> v;
				tempTextures.push_back(DirectX::XMFLOAT2{ u,v });
			}
			if(prefix == "vn")
			{
				float x, y, z;
				iss >> x >> y >> z;
				tempNormales.push_back(DirectX::XMFLOAT3{ x,y,z });
			}

			if (prefix == "f")
			{
				std::vector<uint32_t> faceIndices;
				std::string vertexStr;

				while (iss >> vertexStr)
				{
					int posIndex = 0, texIndex = 0, normIndex = 0;

					size_t firstSlash = vertexStr.find('/');
					size_t secondSlash = vertexStr.find('/', firstSlash + 1);

					if (firstSlash != std::string::npos)
						posIndex = std::stoi(vertexStr.substr(0, firstSlash));
					if (secondSlash != std::string::npos)
						texIndex = std::stoi(vertexStr.substr(firstSlash + 1, secondSlash - firstSlash - 1));
					normIndex = std::stoi(vertexStr.substr(secondSlash + 1));

					Vertex v;
					v.position = tempPosition[posIndex - 1];
					v.textures = tempTextures[texIndex - 1];
					v.normales = tempNormales[normIndex - 1];

					mesh->vertices.push_back(v);

					uint32_t newIndex = static_cast<uint32_t>(mesh->vertices.size() - 1);
					faceIndices.push_back(newIndex);
				}

				for (size_t i = 1; i + 1 < faceIndices.size(); ++i)
				{
					mesh->indices.push_back(faceIndices[0]);
					mesh->indices.push_back(faceIndices[i]);
					mesh->indices.push_back(faceIndices[i + 1]);
				}
			}
		}
		tempPosition.clear();
		tempNormales.clear();
		tempTextures.clear();

		buffer->AddMeshBuffers(mesh,allFile[0].filename().string());
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
