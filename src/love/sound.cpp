#include <vector>
#include <string>
#include "sound.h"
#include "pntr_app.h"
#include "../ChaiLove.h"
#include "Types/Audio/SoundData.h"
//#include "audio/audio_mixer.h"
//#include "audio/conversion/float_to_s16.h"
#include "libretro.h"

using ::ChaiLove;
using love::Types::Audio::SoundData;

namespace love {

bool sound::load(pntr_app* application) {
	app = application;
	m_loaded = true;
	return true;
}

sound::~sound() {
	unload();
}

bool sound::isLoaded() {
	return m_loaded;
}

void sound::unload() {
	for(std::vector<SoundData*>::iterator it = sounds.begin(); it != sounds.end(); ++it) {
		if (*it != NULL) {
			delete *it;
		}
	}
	sounds.clear();

	m_loaded = false;
	app = NULL;
}

SoundData* sound::newSoundData(const std::string& filename) {
	return ChaiLove::getInstance()->audio.newSource(filename);
}

}  // namespace love
