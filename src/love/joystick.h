#ifndef SRC_LOVE_JOYSTICK_H_
#define SRC_LOVE_JOYSTICK_H_

#include <string>
#include <vector>

#include "Types/Input/Joystick.h"
#include "pntr_app.h"

using love::Types::Input::Joystick;

namespace love {

/**
 * Provides an interface to connected joysticks.
 */
class joystick {
	public:
	~joystick();
	void load();
	void update();

	/**
	 * Gets a list of connected Joysticks.
	 *
	 * @return Gets a list of connected Joysticks.
	 */
	std::vector<Joystick*>& getJoysticks();

	/**
	 * Gets the number of connected joysticks.
	 *
	 * @return The number of connected joysticks.
	 */
	int getJoystickCount();

	void unload();

	/**
	 * Checks if a button number is pressed on a joystick.
	 *
	 * @param joystick The joystick to be checked.
	 * @param button The button to be checked.
	 *
	 * @return True if the joystick button is pressed.
	 */
	bool isDown(int joystick, int button);

	/**
	 * Checks if a button is pressed on a joystick.
	 *
	 * ## Example
	 *
	 * @code
	 * if (love.joystick.isDown(0, "left")) {
	 *   love.graphics.print("Joystick is pushed LEFT", 100, 100)
	 * }
	 * @endcode
	 *
	 * @param joystick The joystick to be checked.
	 * @param button The button to be checked.
	 *
	 *
	 * @return True if the joystick button is pressed.
	 */
	bool isDown(int joystick, const std::string& button);

	/**
	 * Retrieve the given joystick.
	 *
	 * ## Example
	 *
	 * @code
	 * if (love.joystick[0].isDown("left")) {
	 *   love.graphics.print("Joystick is pushed LEFT", 100, 100)
	 * }
	 * @endcode
	 *
	 * @param joystick The joystick index to be retrieved.
	 *
	 * @return The joystick of the given player number.
	 */
	Joystick* operator[](int joystick);

	int getButtonKey(const std::string& name);
	std::string getButtonName(int key);

	private:
	std::vector<Joystick*> m_joysticks;
};

}  // namespace love

#endif  // SRC_LOVE_JOYSTICK_H_
