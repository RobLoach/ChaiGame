#include "SoundData.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include "../../../ChaiLove.h"

namespace love {
namespace Types {
namespace Audio {

SoundData::SoundData(const std::string& filename) {
	// Check the extension.
	ChaiLove* app = ChaiLove::getInstance();
	m_sound = pntr_load_sound(filename.c_str());
}

SoundData::~SoundData() {
	unload();
}

void SoundData::unload() {
	if (m_sound != NULL) {
		pntr_unload_sound(m_sound);
		m_sound = NULL;
	}
}

bool SoundData::play() {
	if (isLoaded()) {
		pntr_play_sound(m_sound, m_loop);
		return true;
	}
	return false;
}

bool SoundData::stop() {
	if (isLoaded()) {
		pntr_stop_sound(m_sound);
	}
	return true;
}

bool SoundData::isLoaded() {
	return m_sound != NULL;
}

bool SoundData::isLooping() {
	return m_loop;
}

SoundData& SoundData::setLooping(bool looping) {
	m_loop = looping;
	return *this;
}

}  // namespace Audio
}  // namespace Types
}  // namespace love
