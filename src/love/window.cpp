#include "window.h"
#include <string>
#include "../ChaiLove.h"

#include "pntr_app.h"
#include "config.h"
#include "libretro.h"
#include "Types/Graphics/Point.h"

using ::ChaiLove;
using love::Types::Graphics::Point;

namespace love {

bool window::load(const config& conf) {
	ChaiLove* app = ChaiLove::getInstance();

	// // Initialize SDL.
	// if (SDL_Init(SDL_INIT_VIDEO) == -1) {
	// 	const char* errorChar = SDL_GetError();
	// 	std::string errString("");
	// 	if (errorChar != NULL) {
	// 		errString = errorChar;
	// 	}
	// 	//LibretroLog::log(RETRO_LOG_ERROR) << "[game] Unable to initialize SDL " << errString << std::endl;
	// 	return false;
	// }

	// // Build the Screen.
	// Uint32 flags;
	// if (conf.window.hwsurface) {
	// 	flags = SDL_HWSURFACE;
	// } else {
	// 	flags = SDL_SWSURFACE;
	// }
	// if (conf.window.asyncblit) {
	// 	flags |= SDL_ASYNCBLIT;
	// }
	// if (conf.window.doublebuffering) {
	// 	flags |= SDL_DOUBLEBUF;
	// }
	// app->screen = SDL_SetVideoMode(conf.window.width, conf.window.height, conf.window.bbp, flags);
	// if (app->screen == NULL) {
	// 	const char* errorChar = SDL_GetError();
	// 	std::string errString("");
	// 	if (errorChar != NULL) {
	// 		errString = errorChar;
	// 	}
	// 	//LibretroLog::log(RETRO_LOG_ERROR) << "[game] Unable to initialize SDL" << errString << std::endl;
	// 	SDL_Quit();
	// 	return false;
	// }

	// // Enable video buffering.
	// //app->videoBuffer = (uint32_t *)app->screen->pixels;

	// // Set the title.
	// setTitle(conf.window.title);
	return true;
}

bool window::unload() {
	// // Destroy the screen.
	// ChaiLove* app = ChaiLove::getInstance();
	// if (app->screen != NULL) {
	// 	SDL_FreeSurface(app->screen);
	// 	app->screen = NULL;
	// }

	// // Close SDL.
	// SDL_Quit();
	return true;
}

std::string window::getTitle() {
	return pntr_app_title(ChaiLove::getInstance()->app);
}

window& window::setTitle(const std::string& title) {
	pntr_app_set_title(ChaiLove::getInstance()->app, title.c_str());
	return *this;
}

window& window::showMessageBox(const std::string& msg, int frames) {
	retro_message retroMessage;
	retroMessage.msg = msg.c_str();
	retroMessage.frames = frames;
	ChaiLove::environ_cb(RETRO_ENVIRONMENT_SET_MESSAGE, &retroMessage);
	return *this;
}

window& window::showMessageBox(const std::string& msg) {
	showMessageBox(msg, 1000);
	return *this;
}

}  // namespace love
