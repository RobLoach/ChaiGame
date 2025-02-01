#ifndef SRC_LOVE_TYPES_AUDIO_SOUNDDATA_H_
#define SRC_LOVE_TYPES_AUDIO_SOUNDDATA_H_

#include <string>
#include "audio/audio_mixer.h"

#include "pntr_app.h"

namespace love {
namespace Types {
namespace Audio {

/**
 * Contains audio samples that you can playback.
 */
class SoundData {
	public:
	SoundData(const std::string& filename);
	~SoundData();

	/**
	 * Plays the source.
	 */
	bool play();

	/**
	 * Stops the audio source.
	 */
	bool stop();

	void unload();
	bool isLoaded();

	/**
	 * Returns whether the Source will loop.
	 *
	 * @see setLooping
	 */
	bool isLooping();

	/**
	 * Set whether the Source should loop.
	 *
	 * @see isLooping
	 */
	SoundData& setLooping(bool loop);

	SoundData& setVolume(float volume);
	float getVolume();

	bool isPlaying();

	pntr_sound* m_sound = NULL;
	bool m_loop = false;
	float m_volume = 1.0f;
};

}  // namespace Audio
}  // namespace Types
}  // namespace love

#endif  // SRC_LOVE_TYPES_AUDIO_SOUNDDATA_H_
