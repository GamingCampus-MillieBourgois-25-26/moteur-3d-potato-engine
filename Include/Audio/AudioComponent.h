#pragma once

#include "Component.h"
#include "Audio/AudioManager.h"
#include <memory>
#include <string>

class AudioComponent : public Component
{
public:
	AudioComponent(std::shared_ptr<SoundAsset>);

	void SetSound(std::shared_ptr<SoundAsset>);
	bool PlaySound2D();

	std::shared_ptr<SoundAsset> GetSound();

private:
	std::shared_ptr<SoundAsset> sound;
};