#include "event.h"

#include "../ChaiLove.h"

namespace love {

void event::quit() {
	m_shouldclose = true;
}

void event::update() {
	if (ChaiLove::hasInstance()) {
		// Poll all the inputs.
		ChaiLove::input_poll_cb();

		// TODO(RobLoach): Is polling the SDL events required?
		/*
		while (SDL_PollEvent(&sdlEvent)) {
			switch (sdlEvent.type) {
				case SDL_QUIT:
					quit();
					break;
			}
		}
		*/
	}
}

}  // namespace love
