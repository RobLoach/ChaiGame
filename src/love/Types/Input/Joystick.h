#ifndef SRC_LOVE_TYPES_INPUT_JOYSTICK_H_
#define SRC_LOVE_TYPES_INPUT_JOYSTICK_H_

#include <string>

#include "pntr_app.h"

namespace love {
namespace Types {
namespace Input {

/**
 * Represents a physical joystick.
 */
class Joystick {
	public:
	Joystick();
	Joystick(pntr_app* app, int index);

	/**
	 * Gets the name of the joystick.
	 *
	 * @return string The name of the Joystick.
	 */
	std::string getName();

	pntr_app* m_app;

	/**
	 * Checks if a button on the Joystick is pressed.
	 *
	 * @param button The index of the button to be checked
	 *
	 * @return bool Whether or not the given button is down.
	 */
	bool isDown(int button);

	/**
	 * Checks if a button on the Joystick is pressed.
	 *
	 * @param button The button to be checked
	 *
	 * @return bool Whether or not the given button is down.
	 */
	bool isDown(const std::string& button);

	void update();

	/**
	 * Gets whether the Joystick is connected.
	 *
	 * @return True if the given joystick is connected.
	 */
	bool isConnected();

	/**
	 * Gets the joystick's unique identifier.
	 *
	 * @return The index number of the Joystick.
	 */
	int getID();

	private:
	int m_index = 0;
	bool m_connected = true;
};

}  // namespace Input
}  // namespace Types
}  // namespace love

#endif  // SRC_LOVE_TYPES_INPUT_JOYSTICK_H_
