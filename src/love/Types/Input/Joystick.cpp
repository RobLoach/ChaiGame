#include "Joystick.h"
#include "pntr_app.h"
#include "../../../ChaiLove.h"
#include <string>

namespace love {
namespace Types {
namespace Input {

Joystick::Joystick() {
}

Joystick::Joystick(pntr_app* app, int i) : m_index(i), m_app(app) {
}

bool Joystick::isDown(int button) {
	return pntr_app_gamepad_button_down(m_app, m_index, (pntr_app_gamepad_button)button);
}

bool Joystick::isDown(const std::string& button) {
	int key = ChaiLove::getInstance()->joystick.getButtonKey(button);
	return isDown(key);
}

bool Joystick::isConnected() {
	return m_connected;
}

int Joystick::getID() {
	return m_index;
}

}  // namespace Input
}  // namespace Types
}  // namespace love
