#include <libretro.h>
#include <string>
#include "ChaiLove.h"
#include "pntr_app.h"

ChaiLove* ChaiLove::m_instance = NULL;
retro_input_state_t ChaiLove::input_state_cb = NULL;
retro_input_poll_t ChaiLove::input_poll_cb = NULL;
retro_environment_t ChaiLove::environ_cb = NULL;

void ChaiLove::destroy() {
	pntr_app_log(PNTR_APP_LOG_INFO, "[ChaiLove] Attempting to destroy ChaiLove");
	if (hasInstance()) {
		pntr_app_log(PNTR_APP_LOG_INFO, "[ChaiLove] Destroying ChaiLove");
		m_instance->quit();
		delete m_instance;
		m_instance = NULL;
	}
	pntr_app_log(PNTR_APP_LOG_INFO, "[ChaiLove] Destroyed ChaiLove");
}

ChaiLove* ChaiLove::getInstance() {
	if (!hasInstance()) {
		pntr_app_log(PNTR_APP_LOG_INFO, "[ChaiLove] Initializing ChaiLove");
		m_instance = new ChaiLove;
	}
	return m_instance;
}

bool ChaiLove::hasInstance() {
	return m_instance != NULL;
}

ChaiLove::~ChaiLove() {
	quit();
}

void ChaiLove::quit(void) {
	// Enforce the should close flag.
	event.m_shouldclose = true;

	// Disengage the scripting language.
	if (script) {
		script->exit();
		delete script;
		script = NULL;
	}

	// Unload all the other sub-systems.
	joystick.unload();
	font.unload();
	image.unload();
	sound.unload();
	filesystem.unload();
	window.unload();
}

bool ChaiLove::load(const std::string& file, const void* data, unsigned int dataSize) {
	// Display a welcome message from ChaiLove.
	#ifndef GIT_VERSION
	#define GIT_VERSION ""
	#endif
	std::string version = CHAILOVE_VERSION_STRING GIT_VERSION;
	pntr_app_log_ex(PNTR_APP_LOG_INFO, "[ChaiLove] ChaiLove %s", version.c_str());

	// Iniitalize some of the initial subsystems.
	sound.load(app);
	timer.load(app);

	// Initalize the file system.
	if (!filesystem.init(file, data, dataSize)) {
		pntr_app_log_ex(PNTR_APP_LOG_INFO, "[ChaiLove] [filesystem] Error loading %s", file.c_str());
		return false;
	}

	filesystem.mountlibretro();

	// Initialize the scripting system.
	script = new love::script(file);
	if (!script->mainLoaded) {
		pntr_app_log_ex(PNTR_APP_LOG_INFO, "[ChaiLove] [script] Error loading %s", file);
		return false;
	}
	script->conf(config);
	system.load(config);

	// Load up the window dimensions.
	window.load(app, config);

	graphics.load(app);
	image.load();
	keyboard.load();
	joystick.load(app);
	math.load(app);
	mouse.load(app);
	font.load();

	// Now that all subsystems are loaded, start the script.
	script->load();

	return true;
}

void ChaiLove::update() {
	// Update and poll all the events.
	event.update();

	// Step forward the timer, and update the game.
	if (script != NULL) {
		script->update(pntr_app_delta_time(app));
	}
}

/**
 * Reset the current game.
 */
void ChaiLove::reset() {
	// Tell the script that we are to reset the game.
	pntr_app_log(PNTR_APP_LOG_INFO, "[ChaiLove] Reset");
	if (script != NULL) {
		script->reset();
	}
}

/**
 * Render the ChaiLove.
 */
void ChaiLove::draw() {
	// Clear the screen.
	graphics.clear();

	// Render the game.
	if (script != NULL) {
		script->draw();
	}
}

/**
 * Tell the script to return a string representing the game data.
 */
std::string ChaiLove::savestate() {
	if (script != NULL) {
		return script->savestate();
	}
	return "";
}

/**
 * Ask the script to load the given string.
 */
bool ChaiLove::loadstate(const std::string& data) {
	if (script != NULL) {
		return script->loadstate(data);
	}
	return false;
}

/**
 * Invoke the script cheatreset hook.
 */
void ChaiLove::cheatreset() {
	if (script != NULL) {
		script->cheatreset();
	}
}

/**
 * Invoke the script cheatset hook.
 */
void ChaiLove::cheatset(int index, bool enabled, const std::string& code) {
	if (script != NULL) {
		script->cheatset(index, enabled, code);
	}
}
