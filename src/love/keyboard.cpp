#include "keyboard.h"

#include <string>
#include "../ChaiLove.h"
#include "libretro.h"

namespace love {

bool keyboard::isDown(int scancode) {
	return isScancodeDown(scancode);
}

bool keyboard::isScancodeDown(int scancode) {
	if (scancode > 0 && scancode < RETROK_LAST) {
		return keys[scancode] != 0;
	}

	return false;
}

bool keyboard::isDown(const std::string& key) {
	return isDown(getScancodeFromKey(key));
}

bool keyboard::load() {
	// Initialize the scancode to key mappings with empty strings.
	int i;
	for (i = 0; i < RETROK_LAST; i++) {
		scancodeToKey[i] = "";
	}

	// Initialize the key mappings.
	scancodeToKey[RETROK_UNKNOWN] = "unknown";
	scancodeToKey[RETROK_FIRST] = "first";
	scancodeToKey[RETROK_BACKSPACE] = "backspace";
	scancodeToKey[RETROK_TAB] = "tab";
	scancodeToKey[RETROK_CLEAR] = "clear";
	scancodeToKey[RETROK_RETURN] = "return";
	scancodeToKey[RETROK_PAUSE] = "pause";
	scancodeToKey[RETROK_ESCAPE] = "escape";
	scancodeToKey[RETROK_SPACE] = "space";
	scancodeToKey[RETROK_EXCLAIM] = "!";
	scancodeToKey[RETROK_QUOTEDBL] = "\"";
	scancodeToKey[RETROK_HASH] = "#";
	scancodeToKey[RETROK_DOLLAR] = "$";
	scancodeToKey[RETROK_AMPERSAND] = "&";
	scancodeToKey[RETROK_QUOTE] = "'";
	scancodeToKey[RETROK_LEFTPAREN] = "(";
	scancodeToKey[RETROK_RIGHTPAREN] = ")";
	scancodeToKey[RETROK_ASTERISK] = "*";
	scancodeToKey[RETROK_PLUS] = "+";
	scancodeToKey[RETROK_COMMA] = ",";
	scancodeToKey[RETROK_MINUS] = "-";
	scancodeToKey[RETROK_PERIOD] = ".";
	scancodeToKey[RETROK_SLASH] = "/";
	scancodeToKey[RETROK_0] = "0";
	scancodeToKey[RETROK_1] = "1";
	scancodeToKey[RETROK_2] = "2";
	scancodeToKey[RETROK_3] = "3";
	scancodeToKey[RETROK_4] = "4";
	scancodeToKey[RETROK_5] = "5";
	scancodeToKey[RETROK_6] = "6";
	scancodeToKey[RETROK_7] = "7";
	scancodeToKey[RETROK_8] = "8";
	scancodeToKey[RETROK_9] = "9";
	scancodeToKey[RETROK_COLON] = ":";
	scancodeToKey[RETROK_SEMICOLON] = ";";
	scancodeToKey[RETROK_LESS] = "<";
	scancodeToKey[RETROK_EQUALS] = "=";
	scancodeToKey[RETROK_GREATER] = ">";
	scancodeToKey[RETROK_QUESTION] = "?";
	scancodeToKey[RETROK_AT] = "@";
	scancodeToKey[RETROK_LEFTBRACKET] = "[";
	scancodeToKey[RETROK_BACKSLASH] = "\\";
	scancodeToKey[RETROK_RIGHTBRACKET] = ")";
	scancodeToKey[RETROK_CARET] = "^";
	scancodeToKey[RETROK_UNDERSCORE] = "_";
	scancodeToKey[RETROK_BACKQUOTE] = "`";
	scancodeToKey[RETROK_a] = "a";
	scancodeToKey[RETROK_b] = "b";
	scancodeToKey[RETROK_c] = "c";
	scancodeToKey[RETROK_d] = "d";
	scancodeToKey[RETROK_e] = "e";
	scancodeToKey[RETROK_f] = "f";
	scancodeToKey[RETROK_g] = "g";
	scancodeToKey[RETROK_h] = "h";
	scancodeToKey[RETROK_i] = "i";
	scancodeToKey[RETROK_j] = "j";
	scancodeToKey[RETROK_k] = "k";
	scancodeToKey[RETROK_l] = "l";
	scancodeToKey[RETROK_m] = "m";
	scancodeToKey[RETROK_n] = "n";
	scancodeToKey[RETROK_o] = "o";
	scancodeToKey[RETROK_p] = "p";
	scancodeToKey[RETROK_q] = "q";
	scancodeToKey[RETROK_r] = "r";
	scancodeToKey[RETROK_s] = "s";
	scancodeToKey[RETROK_t] = "t";
	scancodeToKey[RETROK_u] = "u";
	scancodeToKey[RETROK_v] = "v";
	scancodeToKey[RETROK_w] = "w";
	scancodeToKey[RETROK_x] = "x";
	scancodeToKey[RETROK_y] = "y";
	scancodeToKey[RETROK_z] = "z";
	scancodeToKey[RETROK_LEFTBRACE] = "{";
	scancodeToKey[RETROK_BAR] = "|";
	scancodeToKey[RETROK_RIGHTBRACE] = "}";
	scancodeToKey[RETROK_TILDE] = "~";
	scancodeToKey[RETROK_DELETE] = "delete";
	scancodeToKey[RETROK_KP0] = "kp0";
	scancodeToKey[RETROK_KP1] = "kp1";
	scancodeToKey[RETROK_KP2] = "kp2";
	scancodeToKey[RETROK_KP3] = "kp3";
	scancodeToKey[RETROK_KP4] = "kp4";
	scancodeToKey[RETROK_KP5] = "kp5";
	scancodeToKey[RETROK_KP6] = "kp6";
	scancodeToKey[RETROK_KP7] = "kp7";
	scancodeToKey[RETROK_KP8] = "kp8";
	scancodeToKey[RETROK_KP9] = "kp9";
	scancodeToKey[RETROK_KP_PERIOD] = "kp.";
	scancodeToKey[RETROK_KP_DIVIDE] = "kp/";
	scancodeToKey[RETROK_KP_MULTIPLY] = "kp*";
	scancodeToKey[RETROK_KP_MINUS] = "kp-";
	scancodeToKey[RETROK_KP_PLUS] = "kp+";
	scancodeToKey[RETROK_KP_ENTER] = "kpenter";
	scancodeToKey[RETROK_KP_EQUALS] = "kp=";
	scancodeToKey[RETROK_UP] = "up";
	scancodeToKey[RETROK_DOWN] = "down";
	scancodeToKey[RETROK_RIGHT] = "right";
	scancodeToKey[RETROK_LEFT] = "left";
	scancodeToKey[RETROK_INSERT] = "insert";
	scancodeToKey[RETROK_HOME] = "home";
	scancodeToKey[RETROK_END] = "end";
	scancodeToKey[RETROK_PAGEUP] = "pageup";
	scancodeToKey[RETROK_PAGEDOWN] = "pagedown";
	scancodeToKey[RETROK_F1] = "f1";
	scancodeToKey[RETROK_F2] = "f2";
	scancodeToKey[RETROK_F3] = "f3";
	scancodeToKey[RETROK_F4] = "f4";
	scancodeToKey[RETROK_F5] = "f5";
	scancodeToKey[RETROK_F6] = "f6";
	scancodeToKey[RETROK_F7] = "f7";
	scancodeToKey[RETROK_F8] = "f8";
	scancodeToKey[RETROK_F9] = "f9";
	scancodeToKey[RETROK_F10] = "f10";
	scancodeToKey[RETROK_F11] = "f11";
	scancodeToKey[RETROK_F12] = "f12";
	scancodeToKey[RETROK_F13] = "f13";
	scancodeToKey[RETROK_F14] = "f14";
	scancodeToKey[RETROK_F15] = "f15";
	scancodeToKey[RETROK_NUMLOCK] = "numlock";
	scancodeToKey[RETROK_CAPSLOCK] = "capslock";
	scancodeToKey[RETROK_SCROLLOCK] = "scrolllock";
	scancodeToKey[RETROK_RSHIFT] = "rshift";
	scancodeToKey[RETROK_LSHIFT] = "lshift";
	scancodeToKey[RETROK_RCTRL] = "rctrl";
	scancodeToKey[RETROK_LCTRL] = "lctrl";
	scancodeToKey[RETROK_RALT] = "ralt";
	scancodeToKey[RETROK_LALT] = "lalt";
	scancodeToKey[RETROK_RMETA] = "rmeta";
	scancodeToKey[RETROK_LMETA] = "lmeta";
	scancodeToKey[RETROK_LSUPER] = "lgui";
	scancodeToKey[RETROK_RSUPER] = "rgui";
	scancodeToKey[RETROK_MODE] = "mode";
	scancodeToKey[RETROK_COMPOSE] = "compose";
	scancodeToKey[RETROK_HELP] = "help";
	scancodeToKey[RETROK_PRINT] = "printscreen";
	scancodeToKey[RETROK_SYSREQ] = "sysreq";
	scancodeToKey[RETROK_BREAK] = "break";
	scancodeToKey[RETROK_MENU] = "menu";
	scancodeToKey[RETROK_POWER] = "power";
	scancodeToKey[RETROK_EURO] = "currencyunit";
	scancodeToKey[RETROK_UNDO] = "undo";
	scancodeToKey[RETROK_OEM_102] = "oem102";

	// Initialize the key to scancode mappings.
	for (i = 0; i < RETROK_LAST; i++) {
		if (!scancodeToKey[i].empty()) {
			keyToScancode.insert(std::pair<std::string, int> (scancodeToKey[i], i));
		}
	}

	return true;
}

int keyboard::getScancodeFromKey(const std::string& name) {
	return keyToScancode[name];
}

std::string keyboard::getKeyFromScancode(int scancode) {
	return scancodeToKey[scancode];
}

bool keyboard::update() {
	// Go through all keys.
	int16_t state;
	for (int i = 0; i < RETROK_LAST; i++) {
		// Get updated state for each key.
		state = ChaiLove::input_state_cb(0, RETRO_DEVICE_KEYBOARD, 0, i);

		// If the state is different, then issue a keyPressed, or keyReleased.
		if (keys[i] != state) {
			keys[i] = state;

			if (state == 1) {
				eventKeyPressed(i);
			} else {
				eventKeyReleased(i);
			}
		}
	}
	return true;
}

void keyboard::eventKeyPressed(int scancode) {
	std::string key = getKeyFromScancode(scancode);
	ChaiLove* app = ChaiLove::getInstance();
	app->script->keypressed(key, scancode);
}

void keyboard::eventKeyReleased(int scancode) {
	std::string key = getKeyFromScancode(scancode);
	ChaiLove* app = ChaiLove::getInstance();
	app->script->keyreleased(key, scancode);
}

}  // namespace love
