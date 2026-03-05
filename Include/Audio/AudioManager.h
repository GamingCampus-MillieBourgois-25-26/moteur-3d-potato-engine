
#include "SoundAsset.h"
#include <iostream>
#include <unordered_map>
#include <memory>
#include <fstream>
#include <vector>
#include <windows.h>

class AudioManager
{
public:
	AudioManager();
	static AudioManager& Get()
	{
		static AudioManager instance;
		return instance;
	}
	AudioManager(const AudioManager&) = delete;
	AudioManager& operator=(const AudioManager&) = delete;

	std::shared_ptr<SoundAsset> GetSoundPtr(const std::string& soundName);
	bool PlaySound2D(std::shared_ptr<SoundAsset> asset,float volume);
	void Update();
	std::vector<std::filesystem::path> GetExtensionsFile(const std::string& extension);

private:
	ma_engine engine;

	void LoadAllSound();
	std::unordered_map<std::string,std::shared_ptr<SoundAsset>> loadedSound;
	std::vector<std::unique_ptr<ma_sound>> m_ActiveInstances;
	~AudioManager();
};