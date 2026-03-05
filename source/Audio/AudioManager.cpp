#define MINIAUDIO_IMPLEMENTATION
#include "Audio/AudioManager.h"

AudioManager::AudioManager()
{
    ma_engine_init(NULL, &engine);
    LoadAllSound();
}

void AudioManager::LoadAllSound()
{
    std::vector<std::filesystem::path> allFile;
    allFile = GetExtensionsFile(".wav");

    for (const auto& path : allFile)
    {
        std::string key = path.stem().string();
        loadedSound.emplace(
            key,
            std::make_shared<SoundAsset>(&engine, path)
        );
    }

}
std::shared_ptr<SoundAsset> AudioManager::GetSoundPtr(const std::string& soundName)
{
    auto it = loadedSound.find(soundName);
    if(it != loadedSound.end())
    {
        return it->second;
    }
    return nullptr;
}
bool AudioManager::PlaySound2D(std::shared_ptr<SoundAsset> asset)
{
    if (loadedSound.empty())
        return false;

    auto it = loadedSound.begin();
    auto instance = std::make_unique<ma_sound>();

    ma_result result = ma_sound_init_copy(
        &engine,
        &asset->GetTemplate(),
        0,
        NULL,
        instance.get()
    );

    if (result != MA_SUCCESS)
        return false;

    ma_sound_start(instance.get());

    m_ActiveInstances.push_back(std::move(instance));

    return true;
}

std::vector<std::filesystem::path> AudioManager::GetExtensionsFile(const std::string& extension)
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
