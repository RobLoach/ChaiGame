#ifndef SRC_LOVE_SYSTEM_H_
#define SRC_LOVE_SYSTEM_H_

#include <vector>
#include <string>
#include "config.h"

/**
 * This covers all the modules available through ChaiLove.
 *
 * In addition to the modules, there are the callbacks. `load()` is called when loading the game, `update(dt)` when updating the game state, and `draw()` when looking to render the game. The following an example of these callbacks below...
 *
 * @code
 * global x = 20
 * global y = 20
 * global w = 60
 * global h = 20
 *
 * // ChaiLove callback; Load the game.
 * def load() {
 *    // Do something when the game loads.
 * }
 *
 * // ChaiLove callback; Update the game state.
 * def update(dt) {
 *     // Increase the size of the rectangle every frame.
 *     w = w + 1
 *     h = h + 1
 * }
 *
 * // ChaiLove callback; Draw the game.
 * def draw() {
 *     love.graphics.setColor(0, 100, 100)
 *     love.graphics.rectangle("fill", x, y, w, h)
 * }
 * @endcode
 *
 * ## Callbacks
 *
 * - \link love::script::conf conf(t) \endlink Global configuration callback.
 * - \link love::script::load load() \endlink This function is called exactly once at the beginning of the game.
 * - \link love::script::update update(dt) \endlink Callback function used to update the state of the game every frame.
 * - \link love::script::draw draw() \endlink Callback function used to draw on the screen every frame.
 * - \link love::script::reset reset() \endlink Callback function used when the frontend requests to reset the game.
 * - \link love::script::joystickpressed joystickpressed(joy, button) \endlink Called when a joystick button is pressed.
 * - \link love::script::joystickreleased joystickreleased(joy, button) \endlink Called when a joystick button is released.
 * - \link love::script::mousepressed mousepressed(x, y, button) \endlink Called when a mouse button is pressed.
 * - \link love::script::mousereleased mousereleased(x, y, button) \endlink Called when a mouse button is released.
 * - \link love::script::mousemoved mousemoved(x, y, dx, dy) \endlink Callback function triggered when the mouse is moved.
 * - \link love::script::keypressed keypressed(key, scancode) \endlink Callback function triggered when a key is pressed.
 * - \link love::script::keyreleased keyreleased(key, scancode) \endlink Callback function triggered when a key is released.
 * - \link love::script::savestate savestate() \endlink Callback function triggered to export JSON serialized data of the game state.
 * - \link love::script::loadstate loadstate(jsonData) \endlink Callback function triggered to load the given JSON serialized data.
 */
namespace love {

/**
 * Provides access to information about the user's system.
 */
class system {
	public:
	system();

	/**
	 * Gets the current operating system.
	 *
	 * @return The current operating system. "OS X", "Windows", "Linux", "Android" or "iOS".
	 */
	std::string getOS();

	/**
	 * Retreves the running ChaiLove version information.
	 *
	 * @return A vector, with the major being the first element, minor being the second, and patch being the third.
	 *
	 * @see love.system.getVersionString
	 */
	std::vector<int> getVersion();

	/**
	 * Retreves the running ChaiLove version, as a string.
	 *
	 * @return A string representing ChaiLove's version. Example: 1.3.2
	 *
	 * @see love.system.getVersion
	 */
	std::string getVersionString();

	/**
	 * Gets the current user's name, if available. When not available, will return an empty string.
	 *
	 * @return The username of the current user, or an empty string otherwise.
	 */
	std::string getUsername();

	/**
	 * Execute an operating system shell command. This is like the C system() function.
	 *
	 * @param command The command to run.
	 *
	 * @return Returns true or false depending on the process succeeded to execute.
	 */
	bool execute(const std::string& command);

	/**
	 * Gets text from the clipboard.
	 *
	 * Note: This is emulated, and not the actual system clipboard text.
	 *
	 * @return The text currently held in the clipboard.
	 *
	 * @see love.system.setClipboardText
	 */
	std::string getClipboardText();

	/**
	 * Gets text from the clipboard.
	 *
	 * @param text The new text to hold in the system's clipboard.
	 *
	 * @return The system module, for method chaining.
	 *
	 * @see love.system.getClipboardText
	 */
	system& setClipboardText(const std::string& text);
	void updateVariables(config& t);

	bool load(config& t);

	std::string m_username;
	bool m_usernameInitialized = false;
};

}  // namespace love

#endif  // SRC_LOVE_SYSTEM_H_
