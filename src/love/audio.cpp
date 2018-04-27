#include "audio.h"
#include <string>
#include "Types/Audio/SoundData.h"
#include "Types/Audio/AudioState.h"
#include "../ChaiLove.h"
#include "sound.h"
#include "physfs.h"

using love::Types::Audio::SoundData;
using love::Types::Audio::AudioState::Stopped;

namespace love {

void audio::play(SoundData* soundData) {
	if (soundData) {
		soundData->play();
	}
}

SoundData* audio::newSource(const std::string& filename) {
	SoundData* newSound = new SoundData(filename);
	if (newSound->isLoaded()) {
		ChaiLove::getInstance()->sound.sounds.push_back(newSound);
		return newSound;
	}
	return NULL;
}

SoundData* audio::newSource(const std::string& filename, const std::string& type) {
	return newSource(filename);
}

float audio::getVolume() {
	return m_volume;
}

audio& audio::setVolume(float volume) {
	if (volume < 0.0f) {
		volume = 0.0f;
	} else if (volume > 1.0f) {
		volume = 1.0f;
	}
	m_volume = volume;
	return *this;
}

void audio::mixer_render(int16_t *buffer) {
	if (!ChaiLove::hasInstance()) {
		return;
	}

	ChaiLove* app = ChaiLove::getInstance();
	// Clear buffer
	memset(buffer, 0, AUDIO_FRAMES * 2 * sizeof(int16_t));

	// Mix all the sounds together.
	for (std::vector<SoundData*>::size_type i = 0; i != app->sound.sounds.size(); i++) {
		SoundData* currentSound = app->sound.sounds[i];
		if (currentSound == NULL || !currentSound->isLoaded() || currentSound->state == Stopped) {
			continue;
		}

		// Figure out what is playing.
		uint8_t* rawsamples8 = reinterpret_cast<uint8_t*>(calloc(AUDIO_FRAMES * currentSound->bps, sizeof(uint8_t)));
		// bool end = !fread(rawsamples8, sizeof(uint8_t), AUDIO_FRAMES * currentSound->bps, currentSound->sndta.fp);
		PHYSFS_readBytes(currentSound->sndta.fp, rawsamples8, sizeof(uint8_t) * AUDIO_FRAMES * currentSound->bps);
		bool end = PHYSFS_eof(currentSound->sndta.fp);
		int16_t* rawsamples16 = reinterpret_cast<int16_t*>(rawsamples8);
		for (unsigned j = 0; j < AUDIO_FRAMES; j++) {
			int16_t left = 0;
			int16_t right = 0;
			if (currentSound->sndta.head.NumChannels == 1 && currentSound->sndta.head.BitsPerSample ==  8) {
				left = right = rawsamples8[j] * 64;
			}
			if (currentSound->sndta.head.NumChannels == 2 && currentSound->sndta.head.BitsPerSample ==  8) {
				left = rawsamples8[j * 2 + 0] * 64;
				right = rawsamples8[j * 2 + 1] * 64;
			}
			if (currentSound->sndta.head.NumChannels == 1 && currentSound->sndta.head.BitsPerSample == 16) {
				left = right = rawsamples16[j];
			}
			if (currentSound->sndta.head.NumChannels == 2 && currentSound->sndta.head.BitsPerSample == 16) {
				left = rawsamples16[j * 2 + 0];
				right = rawsamples16[j * 2 +  1];
			}
			buffer[j * 2 + 0] += left  * currentSound->getVolume() * m_volume;
			buffer[j * 2 + 1] += right * currentSound->getVolume() * m_volume;
		}

		if (end) {
			if (currentSound->loop) {
				currentSound->play();
			} else {
				currentSound->stop();
			}
		}

		free(rawsamples8);
	}
}

}  // namespace love
