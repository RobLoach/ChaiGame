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

void joystick::load() {
	int numberOfJoysticks = 4;
	for (int i = 0; i < numberOfJoysticks; i++) {
		Joystick* joystick = new Joystick(i);
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

void joystick::update() {
	for (std::vector<Joystick*>::iterator it = m_joysticks.begin(); it != m_joysticks.end(); ++it) {
		(*it)->update();
	}
}

Joystick* joystick::operator[](int joystick) {
	if (joystick < 0) {
		joystick = 0;
	} else if (joystick >= getJoystickCount()) {
		joystick = getJoystickCount() - 1;
	}
	return m_joysticks[joystick];
}

std::string joystick::getButtonName(int key) {
	switch (key) {
		case RETRO_DEVICE_ID_JOYPAD_A:
			return "a";
		case RETRO_DEVICE_ID_JOYPAD_B:
			return "b";
		case RETRO_DEVICE_ID_JOYPAD_X:
			return "x";
		case RETRO_DEVICE_ID_JOYPAD_Y:
			return "y";
		case RETRO_DEVICE_ID_JOYPAD_SELECT:
			return "select";
		case RETRO_DEVICE_ID_JOYPAD_START:
			return "start";
		case RETRO_DEVICE_ID_JOYPAD_L:
			return "l1";
		case RETRO_DEVICE_ID_JOYPAD_R:
			return "r1";
		case RETRO_DEVICE_ID_JOYPAD_L2:
			return "l2";
		case RETRO_DEVICE_ID_JOYPAD_R2:
			return "r2";
		case RETRO_DEVICE_ID_JOYPAD_L3:
			return "l3";
		case RETRO_DEVICE_ID_JOYPAD_R3:
			return "r3";
		case RETRO_DEVICE_ID_JOYPAD_UP:
			return "up";
		case RETRO_DEVICE_ID_JOYPAD_DOWN:
			return "down";
		case RETRO_DEVICE_ID_JOYPAD_LEFT:
			return "left";
		case RETRO_DEVICE_ID_JOYPAD_RIGHT:
			return "right";
	}

	return "unknown";
}

int joystick::getButtonKey(const std::string& name) {
	if (name == "a") {
		return RETRO_DEVICE_ID_JOYPAD_A;
	}
	if (name == "b") {
		return RETRO_DEVICE_ID_JOYPAD_B;
	}
	if (name == "x") {
		return RETRO_DEVICE_ID_JOYPAD_X;
	}
	if (name == "y") {
		return RETRO_DEVICE_ID_JOYPAD_Y;
	}
	if (name == "select" || name == "back") {
		return RETRO_DEVICE_ID_JOYPAD_SELECT;
	}
	if (name == "start") {
		return RETRO_DEVICE_ID_JOYPAD_START;
	}
	if (name == "l1" || name == "leftshoulder") {
		return RETRO_DEVICE_ID_JOYPAD_L;
	}
	if (name == "r1" || name == "rightshoulder") {
		return RETRO_DEVICE_ID_JOYPAD_R;
	}
	if (name == "l2") {
		return RETRO_DEVICE_ID_JOYPAD_L2;
	}
	if (name == "r2") {
		return RETRO_DEVICE_ID_JOYPAD_R2;
	}
	if (name == "l3") {
		return RETRO_DEVICE_ID_JOYPAD_L3;
	}
	if (name == "r3") {
		return RETRO_DEVICE_ID_JOYPAD_R3;
	}
	if (name == "up" || name == "dpup") {
		return RETRO_DEVICE_ID_JOYPAD_UP;
	}
	if (name == "down" || name == "dpdown") {
		return RETRO_DEVICE_ID_JOYPAD_DOWN;
	}
	if (name == "left" || name == "dpleft") {
		return RETRO_DEVICE_ID_JOYPAD_LEFT;
	}
	if (name == "right" || name == "dpriht") {
		return RETRO_DEVICE_ID_JOYPAD_RIGHT;
	}
	return -1;
}

}  // namespace love
