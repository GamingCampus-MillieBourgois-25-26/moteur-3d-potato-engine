#define STB_IMAGE_IMPLEMENTATION
#include "Texture/TextureManager.h"
#include <iostream>

TextureManager::TextureManager(ID3D11Device* device)
    : m_Device(device)
{
    LoadAll();
}

std::shared_ptr<Texture> TextureManager::Load(const std::string& name)
{
    std::filesystem::path fullPath = m_Root / name;
    fullPath = fullPath.lexically_normal();

    std::string key = fullPath.string();

    auto it = m_Textures.find(key);
    if (it != m_Textures.end())
        return it->second;

    if (!std::filesystem::exists(fullPath))
    {
        std::cerr << "Texture introuvable : " << key << std::endl;
        return nullptr;
    }

    auto texture = std::make_shared<Texture>();
    if (!texture->Load(m_Device, key))
    {
        std::cerr << "Erreur chargement texture : " << key << std::endl;
        return nullptr;
    }
    m_Textures[key] = texture;

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
