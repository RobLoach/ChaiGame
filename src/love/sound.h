#ifndef SRC_LOVE_SOUND_H_
#define SRC_LOVE_SOUND_H_

#include "Types/Audio/SoundData.h"
#include <vector>
#include "libretro.h"

namespace love {

/**
 * This module is responsible for decoding sound files. It can't play the sounds, see love.audio for that.
 */
class sound {
	public:
	bool load();
	bool isLoaded();
	bool hasAudio();
	void unload();
	void update();
	~sound();


	// void convert_float_to_s16(int16_t *out, const float *in, size_t samples);

	/**
	 * Creates a new SoundData.
	 *
	 * @param filename The file name of the file to load.
	 *
	 * @return A new SoundData object, NULL if loading failed.
	 */
	Types::Audio::SoundData* newSoundData(const std::string& filename);

	std::vector<Types::Audio::SoundData*> sounds;

	bool m_loaded = false;

	retro_audio_sample_t audio_cb = NULL;
	retro_audio_sample_batch_t audio_batch_cb = NULL;
};

}  // namespace love

#endif  // SRC_LOVE_SOUND_H_
