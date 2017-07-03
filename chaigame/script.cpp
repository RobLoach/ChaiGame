#include "script.h"
#include "chaigame.h"
#include "../Application.h"
//#include "filesystem.h"

#ifdef __HAVE_CHAISCRIPT__
using namespace chaiscript;
#endif

namespace chaigame {
	void script::loadModule(const std::string& moduleName) {
		#ifdef __HAVE_CHAISCRIPT__
		Application* app = Application::getInstance();
		std::string contents = app->filesystem.read(moduleName);
		chai.eval(contents);
		#endif
	}

	script::script() {
		#ifdef __HAVE_CHAISCRIPT__
		Application* app = Application::getInstance();

		// Register the Graphics module.
		chai.add(fun(&graphics::rectangle), "rectangle");
		chai.add(fun(&graphics::newImage), "newImage");
		chai.add(fun(&graphics::print), "print");
		chai.add(fun(&graphics::setColor), "setColor");
		chai.add(fun<void, graphics, Image*, int, int>(&graphics::draw), "draw");
		chai.add_global(var(std::ref(app->graphics)), "graphics");

		// Register the Keyboard module.
		chai.add(fun(&keyboard::update), "update");
		chai.add(fun(&keyboard::isDown), "isDown");
		chai.add_global(var(std::ref(app->keyboard)), "keyboard");

		// Register the Image module.
		chai.add(fun(&image::newImageData), "newImageData");
		chai.add_global(var(std::ref(app->image)), "image");

		// Register the Filesystem module.
		chai.add(fun(&filesystem::read), "read");
		chai.add_global(var(std::ref(app->filesystem)), "filesystem");

		// Register the System module.
		chai.add(fun(&system::getOS), "getOS");
		chai.add(fun(&system::loadModule), "loadModule");
		chai.add_global(var(std::ref(app->system)), "system");

		// Register the Sound module.
		chai.add(fun(&sound::newSoundData), "newSoundData");
		chai.add_global(var(std::ref(app->sound)), "sound");

		// Register the Audio module.
		chai.add(fun(&audio::play), "play");
		chai.add_global(var(std::ref(app->audio)), "audio");

		// Register the Joystick module.
		chai.add(fun(&joystick::getJoysticks), "getJoysticks");
		chai.add(fun(&joystick::getJoystickCount), "getJoystickCount");
		chai.add(fun<bool, joystick, int, const std::string&>(&joystick::isDown), "isDown");
		chai.add_global(var(std::ref(app->joystick)), "joystick");

		// Load main.chai.
		loadModule("main.chai");

		// Find the game functions.
		chaiload = chai.eval<std::function<void ()> >("load");
		chaiupdate = chai.eval<std::function<void (float)> >("update");
		chaidraw = chai.eval<std::function<void ()> >("draw");
		#endif
	}

	void script::load() {
		#ifdef __HAVE_CHAISCRIPT__
		chaiload();
		#endif
	}

	void script::update(float delta) {
		#ifdef __HAVE_CHAISCRIPT__
		chaiupdate(delta);
		#endif
	}

	void script::draw() {
		#ifdef __HAVE_CHAISCRIPT__
		chaidraw();
		#endif
	}
}
