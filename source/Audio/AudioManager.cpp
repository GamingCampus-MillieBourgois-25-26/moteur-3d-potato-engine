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
AudioManager::~AudioManager()
{
        for (auto& sound : m_ActiveInstances)
        {
            if (sound)
            {
                ma_sound_uninit(sound.get());
            }
        }

        m_ActiveInstances.clear();
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
bool AudioManager::PlaySound2D(std::shared_ptr<SoundAsset> asset, float volume)
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

    ma_sound_set_volume(instance.get(), volume);
    ma_sound_start(instance.get());

    m_ActiveInstances.push_back(std::move(instance));

    return true;
}

void AudioManager::Update()
{
    m_ActiveInstances.erase(
        std::remove_if(
            m_ActiveInstances.begin(),
            m_ActiveInstances.end(),
            [](std::unique_ptr<ma_sound>& sound)
            {
                if (ma_sound_at_end(sound.get()))
                {
                    ma_sound_uninit(sound.get());
                    return true;
                }

                return false;
            }),
        m_ActiveInstances.end()
    );
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
