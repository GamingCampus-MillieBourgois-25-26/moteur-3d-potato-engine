#include "Texture/TextureManager.h"
#include <iostream>

TextureManager::TextureManager(ID3D11Device* device)
    : m_Device(device)
{
    LoadAll();
}

std::shared_ptr<Texture> TextureManager::Load(const std::string& path)
{
    auto it = m_Textures.find(path);
    if (it != m_Textures.end())
    {
        return it->second;
    }
    auto texture = std::make_shared<Texture>();

    if (!texture->Load(m_Device, path))
    {
        std::cout << "TextureManager: Failed to load " << path << std::endl;
        return nullptr;
    }

    m_Textures[path] = texture;

    return texture;
}

std::vector<std::filesystem::path>
TextureManager::GetExtensionsFile(const std::vector<std::string>& extensions)
{
    std::filesystem::path folder = "assets";
    std::vector<std::filesystem::path> files;

    if (!std::filesystem::exists(folder))
    {
        std::cout << "TextureManager: assets folder not found.\n";
        return files;
    }

    for (const auto& entry : std::filesystem::recursive_directory_iterator(folder))
    {
        if (!entry.is_regular_file())
            continue;

        std::string ext = entry.path().extension().string();

        for (const auto& allowed : extensions)
        {
            if (ext == allowed)
            {
                files.push_back(entry.path());
                break;
            }
        }
    }

    return files;
}

void TextureManager::Clear()
{
    m_Textures.clear();
}

void TextureManager::LoadAll()
{
    std::vector<std::string> extensions =
    {
        ".png",
        ".jpg",
        ".jpeg",
        ".bmp",
        ".tga"
    };

    auto allFiles = GetExtensionsFile(extensions);

    for (const auto& path : allFiles)
    {
        std::string normalizedPath = path.generic_string();

        auto texture = Load(normalizedPath);

        if (texture)
        {
            std::cout << "Loaded texture: " << normalizedPath << std::endl;
        }
    }

    std::cout << "TextureManager: Loaded "
        << m_Textures.size()
        << " textures.\n";
}
