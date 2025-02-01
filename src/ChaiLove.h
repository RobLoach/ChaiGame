/**
 * \mainpage ChaiLove API
 *
 * [ChaiLove](https://github.com/libretro/libretro-chailove) is a framework for making 2D games in the [ChaiScript scripting language](http://chaiscript.com/). ChaiLove is totally free, and can be used in anything from friendly open-source hobby projects, to evil, closed-source commercial ones.
 *
 * Some interesting places to go from here:
 * - \link gettingstarted Getting Started \endlink
 * - \link ::love love \endlink (the module)
 * - \link love::script Callbacks \endlink All the callbacks that are executed.
 * - \link games Games \endlink
 * - [Examples](https://git.io/vxPmn)
 * - [Building ChaiLove](https://github.com/libretro/libretro-chailove#development)
 *
 * ## ChaiScript
 *
 * Never used ChaiScript before? It's a really cool language! This manual won't teach you ChaiScript, but fortunately there are other good resources for that.
 *
 * - [ChaiScript Cheatsheet](https://git.io/vxPqI)
 * - [ChaiScript Documentation](http://chaiscript.com/docs.html)
 *
 * ## Hello World
 *
 * This is the full source for "hello world" in ChaiLove, using a `main.chai` file. Running this code will cause an 640 by 480 window to appear, and display white text on a black background.
 *
 * @code
 * def load() {
 * 	 global logo = love.graphics.newImage("logo.png")
 *   global x = 10.0f
 * }
 *
 * def draw() {
 *   love.graphics.print("Hello World!", 400, 300)
 *   love.graphics.draw(logo, x, 100)
 * }
 *
 * def update(dt) {
 *   x = x + 20.0f * dt
 * }
 * @endcode
 *
 * To run the above, execute it with `retroarch -L chailove_libretro.so main.chai` .
 */

#ifndef SRC_CHAILOVE_H_
#define SRC_CHAILOVE_H_

#define CHAILOVE_VERSION_MAJOR 2
#define CHAILOVE_VERSION_MINOR 0
#define CHAILOVE_VERSION_PATCH 0
#define CHAILOVE_VERSION_STRING "2.0.0-pre"

#include <string>

#include "pntr_app.h"
#include "libretro.h"

#include "love/keyboard.h"
#include "love/config.h"
#include "love/data.h"
#include "love/script.h"
#include "love/filesystem.h"
#include "love/graphics.h"
#include "love/image.h"
#include "love/system.h"
#include "love/sound.h"
#include "love/font.h"
#include "love/timer.h"
#include "love/audio.h"
#include "love/joystick.h"
#include "love/mouse.h"
#include "love/window.h"
#include "love/math.h"
#include "love/event.h"

class ChaiLove {
	public:
	static ChaiLove* getInstance();
	static ChaiLove* m_instance;
	static void destroy();
	static bool hasInstance();

	static retro_input_state_t input_state_cb;
	static retro_input_poll_t input_poll_cb;
	static retro_environment_t environ_cb;

	love::config config;
	love::keyboard keyboard;
	love::script* script = NULL;
	love::data data;
	love::filesystem filesystem;
	love::graphics graphics;
	love::image image;
	love::system system;
	love::sound sound;
	love::font font;
	love::timer timer;
	love::audio audio;
	love::joystick joystick;
	love::mouse mouse;
	love::math math;
	love::window window;
	love::event event;

	~ChaiLove();
	void quit(void);
	bool load(const std::string& file, const void* data, unsigned int dataSize);
	void update();
	void draw();
	void reset();
	std::string savestate();
	bool loadstate(const std::string& data);
	void cheatreset();
	void cheatset(int index, bool enabled, const std::string& code);

	pntr_image* screen = NULL;
	pntr_app* app = NULL;
};

#endif  // SRC_CHAILOVE_H_
