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
	//audio_mixer_init(44100);
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

	// Close the audio mixer.
	//audio_mixer_done();
	m_loaded = false;
	app = NULL;
}


SoundData* sound::newSoundData(const std::string& filename) {
	return ChaiLove::getInstance()->audio.newSource(filename);
}

void sound::update() {
	// int bufferSize = 44100 / 60;
	// float samples[1470] = { 0 };  // 44100 / 60 * 2
	// int16_t samples2[1470] = { 0 };  // 44100 / 60 * 2
	// audio_mixer_mix(samples, bufferSize, 1.0, false);
	// convert_float_to_s16(samples2, samples, 2 * bufferSize);
	// audio_batch_cb(samples2, bufferSize);
}


}  // namespace love
