#pragma once
#include "Texture.h"
#include <filesystem>
#include <unordered_map>
#include <memory>
#include <string>
#include <fstream>

class TextureManager
{
public:
    TextureManager(ID3D11Device* device);
    ~TextureManager() = default;

    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;

    std::shared_ptr<Texture> Load(const std::string& path);
    std::vector<std::filesystem::path> GetExtensionsFile(const std::vector<std::string>& extensions);

    void Clear();

private:
    void LoadAll();
    ID3D11Device* m_Device = nullptr;
    std::filesystem::path m_Root = "assets/textures/";
    std::unordered_map<std::string, std::shared_ptr<Texture>> m_Textures;
};