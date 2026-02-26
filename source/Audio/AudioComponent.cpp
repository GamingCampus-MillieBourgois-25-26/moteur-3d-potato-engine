#include "Audio/AudioComponent.h"

AudioComponent::AudioComponent(std::shared_ptr<SoundAsset> _sound): sound(_sound)
{
}

void AudioComponent::SetSound(std::shared_ptr<SoundAsset> newSound) { sound = newSound; }

bool AudioComponent::PlaySound2D()
{
	return AudioManager::Get().PlaySound2D(sound);
}

std::shared_ptr<SoundAsset> AudioComponent::GetSound() { return sound; }
