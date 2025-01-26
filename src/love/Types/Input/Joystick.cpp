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

void Joystick::update() {
	// if (!isConnected()) {
	// 	return;
	// }

	// int16_t state;
	// // Loop through each button.
	// for (int u = 0; u < 14; u++) {
	// 	// Retrieve the state of the button.
	// 	state = ChaiLove::input_state_cb(m_index, RETRO_DEVICE_JOYPAD, 0, u);

	// 	// Check if there's a change of state.
	// 	if (m_state[u] != state) {
	// 		m_state[u] = state;

	// 		std::string name = ChaiLove::getInstance()->joystick.getButtonName(u);
	// 		if (state == 1) {
	// 			ChaiLove::getInstance()->script->joystickpressed(m_index, name);
	// 		} else if (state == 0) {
	// 			ChaiLove::getInstance()->script->joystickreleased(m_index, name);
	// 		}
	// 	}
	// }
}

}  // namespace Input
}  // namespace Types
}  // namespace love
