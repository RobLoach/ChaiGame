#include <string>
#include "SDL.h"

#include "libretro.h"
#include "Game.h"
#include "chaigame/log.h"

Game* Game::m_instance = NULL;
retro_input_state_t Game::input_state_cb = NULL;
retro_input_poll_t Game::input_poll_cb = NULL;

void Game::destroy() {
	m_instance = NULL;
}

Game* Game::getInstance() {
	if (!m_instance) {
		m_instance = new Game;
	}
	return m_instance;
}

void Game::quit(void) {
	// Quit all the subsystems.
	joystick.unload();
	font.unload();
	image.unload();
	sound.unload();
	filesystem.unload();
	window.unload();
	chaigame::log()->info("Finish");
}

bool Game::load(const std::string& file) {
	// Initalize all the subsystems.
	chaigame::log()->info("Welcome to ChaiGame");
	filesystem.init(file);
	script = new chaigame::script();
	script->conf(config);

	#ifdef __HAVE_TESTS__
	test.conf(config);
	#endif

	window.load(config);

	if (config.modules.sound) {
		sound.load();
	}

	graphics.load();
	image.load();
	keyboard.load();
	joystick.load();
	math.load();
	mouse.load();
	font.load();
	script->load();

	#ifdef __HAVE_TESTS__
	test.load();
	#endif

	return true;
}

bool Game::update() {
	if (event.quitstatus) {
		return false;
	}

	sound.update();

	// Poll all SDL events.
	while (SDL_PollEvent(&sdlEvent)) {
		switch (sdlEvent.type) {
			case SDL_QUIT:
				event.quit();
				return !event.quitstatus;
				break;
			case SDL_MOUSEMOTION:
				mouse.motionEvent(sdlEvent.motion);
				break;
			case SDL_MOUSEBUTTONDOWN:
				mouse.buttonEvent(sdlEvent.button);
				break;
			case SDL_MOUSEBUTTONUP:
				mouse.buttonEvent(sdlEvent.button);
				break;
		}
	}

	// Update some of the sub-systems.
	joystick.update();
	keyboard.update();

	// Step forward the timer, and update the game.
	script->update(timer.getDelta());

	#ifdef __HAVE_TESTS__
	test.update(timer.getDelta());
	#endif

	return !event.quitstatus;
}

/**
 * Reset the current game.
 */
void Game::reset() {
	// Tell the script that we are to reset the game.
	chaigame::log()->info("[game] Reset");
	script->reset();
}

/**
 * Render the Game.
 */
void Game::draw() {
	if (!event.quitstatus) {
		// Clear the screen.
		graphics.clear();

		// Render the game.
		script->draw();

		#ifdef __HAVE_TESTS__
		test.draw();
		#endif

		// Flip the buffer.
		GPU_Flip(screen);
	}
}

/**
 * Tell the script to return a string representing the game data.
 */
std::string Game::savestate() {
	return script->savestate();
}

/**
 * Ask the script to load the given string.
 */
bool Game::loadstate(std::string data) {
	return script->loadstate(data);
}
