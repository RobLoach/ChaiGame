#ifndef SRC_LOVE_KEYBOARD_H_
#define SRC_LOVE_KEYBOARD_H_

#include <string>
#include <map>

#include "libretro.h"

#include "pntr_app.h"

namespace love {
/**
 * Provides an interface to the user's keyboard.
 */
class keyboard {
	public:
	bool load();

	/**
	 * Checks whether a certain key is down.
	 *
	 * @param key The key to check.
	 *
	 * @return True if the key is down, false if not.
	 */
	bool isDown(const std::string& key);

	/**
	 * Checks whether a certain key is down.
	 *
	 * @param scancode The key scancode to check.
	 *
	 * @return True if the key is down, false if not.
	 */
	bool isDown(int scancode);

	/**
	 * Checks whether a certain key is down.
	 *
	 * @param scancode The key scancode to check.
	 *
	 * @return True if the key is down, false if not.
	 */
	bool isScancodeDown(int scancode);

	/**
	 * Retrieve a scancode from the given key.
	 *
	 * @see love.keyboard.getKeyFromScancode
	 */
	int getScancodeFromKey(const std::string& key);

	/**
	 * Retrieve a key from the given scancode.
	 *
	 * @see love.keyboard.getScancodeFromKey
	 */
	std::string getKeyFromScancode(int scancode);

	std::map<std::string, int> keyToScancode;
	std::string scancodeToKey[PNTR_APP_KEY_LAST] = {};
	short int keys[PNTR_APP_KEY_LAST] = {};

	void eventKeyPressed(int key);
	void eventKeyReleased(int key);
};

}  // namespace love

#endif  // SRC_LOVE_KEYBOARD_H_
