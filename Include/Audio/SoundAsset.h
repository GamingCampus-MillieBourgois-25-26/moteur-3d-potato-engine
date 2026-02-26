#include "miniaudio/miniaudio.h"
#include <filesystem>

class SoundAsset
{
public:
    SoundAsset(ma_engine* engine, const std::filesystem::path& path)
        {
            ma_sound_init_from_file(
                engine,
                path.string().c_str(),
                MA_SOUND_FLAG_DECODE,
                NULL,
                NULL,
                &sound
            );
        }

        ~SoundAsset()
        {
            ma_sound_uninit(&sound);
        }

        ma_sound& GetTemplate() { return sound; }

private:
    ma_sound sound;
};