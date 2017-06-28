#include <string>
#include <SDL.h>

#include "Application.h"
#include "chaigame/chaigame.h"

#include <iostream>

Application* Application::m_instance = NULL;

bool Application::isRunning() {
	return m_instance != NULL;
}
void Application::destroy() {
	m_instance = NULL;
}

Application* Application::getInstance() {
	if (!m_instance) {
		m_instance = new Application;
	}
	return m_instance;
}

void Application::quit(void) {
	filesystem.unload();
	sound.unload();
	image.unload();
	// Tell SDL to quit.
	SDL_Quit();
}

bool Application::load(const std::string& file) {
	// Initialize SDL.
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		return false;
	}

	// Build the Screen.
	screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE | SDL_SRCALPHA | SDL_RESIZABLE);
	if (screen == NULL) {
		SDL_Quit();
		return false;
	}

	// Enable video buffering.
	videoBuffer = (unsigned int *)screen->pixels;

	// Fix alpha blending.
	if (SDL_SetAlpha(screen, SDL_SRCALPHA, 0) == -1) {
		// Error: Do nothing.
	}

	// Disable the mouse cursor from showing up.
	SDL_ShowCursor(SDL_DISABLE);

	// Initalize the chaigame subsystems.
	sound.load();
	keyboard.load();
	graphics.load();
	image.load();
	filesystem.load(file);
	script = new chaigame::script();
	script->load();

	// Set up the game timer.
	tick = SDL_GetTicks();

	return true;
}

bool Application::update() {
	// Poll all SDL events.
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				return false;
				break;
		}
	}

	// Update any of the sub-systems.
	keyboard.update();
	sound.update();

	// Retrieve the new game time.
	Uint32 current = SDL_GetTicks();

	// Update the game.
	script->update(current - tick);

	// Update the timer.
	tick = current;

	return true;
}

/**
 * Render the application.
 */
void Application::draw(){
	// Clear the screen
	Uint32 color = SDL_MapRGBA(screen->format, 0, 0, 0, 255);
	SDL_FillRect(screen, NULL, color);

	// Test drawing a rectangle.
	static int x = 10;
	static int y = 10;

	if (keyboard.isDown("up")) {
		y -= 6;
	}
	if (keyboard.isDown("down")) {
		y += 6;
	}
	if (keyboard.isDown("left")) {
		x -= 6;
	}
	if (keyboard.isDown("right")) {
		x += 6;
	}
	graphics.rectangle(x, y, 100, 100, 0, 255, 255, 255);


	graphics.print("Hello World!", 100, 300);
	//static chaigame::Image* pic = graphics.newImage("logo.png");
	//graphics.draw(pic, x, y);

	// Render the game.
	script->draw();

	// Update the screen.
	SDL_UpdateRect(screen, 0, 0, 0, 0);
	SDL_Flip(screen);
}
