#include "audio.h"
#include <string>
#include "Types/Audio/SoundData.h"
#include "../ChaiLove.h"
#include "sound.h"
#include "audio/conversion/float_to_s16.h"

using love::Types::Audio::SoundData;

namespace love {

bool audio::play(SoundData* soundData) {
    if (soundData == NULL) {
        return false;
    }
    return soundData->play();
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
}  // namespace love
