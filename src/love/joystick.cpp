#include "joystick.h"
#include "pntr_app.h"
#include <string>
#include <vector>
#include <libretro.h>
#include "Types/Input/Joystick.h"
#include "../ChaiLove.h"

using love::Types::Input::Joystick;
using ::ChaiLove;

namespace love {

joystick::~joystick() {
	unload();
}

std::vector<Joystick*>& joystick::getJoysticks() {
	return m_joysticks;
}

void joystick::load(pntr_app* app) {
	m_app = app;
	int numberOfJoysticks = 4;
	for (int i = 0; i < numberOfJoysticks; i++) {
		Joystick* joystick = new Joystick(app, i);
		m_joysticks.push_back(joystick);
	}
}

void joystick::unload() {
	for (std::vector<Joystick*>::iterator it = m_joysticks.begin(); it != m_joysticks.end(); ++it) {
		if (*it != NULL) {
	    	delete *it;
	    }
	}
	m_joysticks.clear();
}

int joystick::getJoystickCount() {
	return m_joysticks.size();
}

bool joystick::isDown(int joystick, int button) {
	return m_joysticks[joystick]->isDown(button);
}

bool joystick::isDown(int joystick, const std::string& button) {
	return m_joysticks[joystick]->isDown(button);
}

Joystick* joystick::operator[](int joystick) {
	if (joystick < 0 || joystick >= getJoystickCount()) {
		return NULL;
	}

	return m_joysticks[joystick];
}

std::string joystick::getButtonName(int key) {
	switch (key) {
		case PNTR_APP_GAMEPAD_BUTTON_A:
			return "a";
		case PNTR_APP_GAMEPAD_BUTTON_B:
			return "b";
		case PNTR_APP_GAMEPAD_BUTTON_X:
			return "x";
		case PNTR_APP_GAMEPAD_BUTTON_Y:
			return "y";
		case PNTR_APP_GAMEPAD_BUTTON_SELECT:
			return "back";
		case PNTR_APP_GAMEPAD_BUTTON_START:
			return "start";
		case PNTR_APP_GAMEPAD_BUTTON_LEFT_SHOULDER:
			return "leftshoulder";
		case PNTR_APP_GAMEPAD_BUTTON_RIGHT_SHOULDER:
			return "rightshoulder";
		case PNTR_APP_GAMEPAD_BUTTON_MENU:
			return "guide";
		case PNTR_APP_GAMEPAD_BUTTON_UP:
			return "dpup";
		case PNTR_APP_GAMEPAD_BUTTON_DOWN:
			return "dpdown";
		case PNTR_APP_GAMEPAD_BUTTON_LEFT:
			return "dpleft";
		case PNTR_APP_GAMEPAD_BUTTON_RIGHT:
			return "dpright";
	}

	return "unknown";
}

int joystick::getButtonKey(const std::string& name) {
	// TODO: Build a pair map of the buttons so this is faster
	if (name == "a") {
		return PNTR_APP_GAMEPAD_BUTTON_A;
	}
	if (name == "b") {
		return PNTR_APP_GAMEPAD_BUTTON_B;
	}
	if (name == "x") {
		return PNTR_APP_GAMEPAD_BUTTON_X;
	}
	if (name == "y") {
		return PNTR_APP_GAMEPAD_BUTTON_Y;
	}
	if (name == "select" || name == "back") {
		return PNTR_APP_GAMEPAD_BUTTON_SELECT;
	}
	if (name == "start") {
		return PNTR_APP_GAMEPAD_BUTTON_START;
	}
	if (name == "guide") {
		return PNTR_APP_GAMEPAD_BUTTON_MENU;
	}
	if (name == "l1" || name == "leftshoulder") {
		return PNTR_APP_GAMEPAD_BUTTON_LEFT_SHOULDER;
	}
	if (name == "r1" || name == "rightshoulder") {
		return PNTR_APP_GAMEPAD_BUTTON_RIGHT_SHOULDER;
	}
	if (name == "up" || name == "dpup") {
		return PNTR_APP_GAMEPAD_BUTTON_UP;
	}
	if (name == "down" || name == "dpdown") {
		return PNTR_APP_GAMEPAD_BUTTON_DOWN;
	}
	if (name == "left" || name == "dpleft") {
		return PNTR_APP_GAMEPAD_BUTTON_LEFT;
	}
	if (name == "right" || name == "dpright") {
		return PNTR_APP_GAMEPAD_BUTTON_RIGHT;
	}
	return -1;
}

}  // namespace love
