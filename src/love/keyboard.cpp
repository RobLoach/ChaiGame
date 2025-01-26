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
	scancodeToKey[PNTR_APP_KEY_INVALID] = "";
	scancodeToKey[PNTR_APP_KEY_FIRST] = "";
	scancodeToKey[PNTR_APP_KEY_SPACE] = " ";
	scancodeToKey[PNTR_APP_KEY_APOSTROPHE] = "'";
	scancodeToKey[PNTR_APP_KEY_COMMA] = ",";
	scancodeToKey[PNTR_APP_KEY_MINUS] = "-";
	scancodeToKey[PNTR_APP_KEY_PERIOD] = ".";
	scancodeToKey[PNTR_APP_KEY_SLASH] = "/";
	scancodeToKey[PNTR_APP_KEY_0] = "0";
	scancodeToKey[PNTR_APP_KEY_1] = "1";
	scancodeToKey[PNTR_APP_KEY_2] = "2";
	scancodeToKey[PNTR_APP_KEY_3] = "3";
	scancodeToKey[PNTR_APP_KEY_4] = "4";
	scancodeToKey[PNTR_APP_KEY_5] = "5";
	scancodeToKey[PNTR_APP_KEY_6] = "6";
	scancodeToKey[PNTR_APP_KEY_7] = "7";
	scancodeToKey[PNTR_APP_KEY_8] = "8";
	scancodeToKey[PNTR_APP_KEY_9] = "9";
	scancodeToKey[PNTR_APP_KEY_SEMICOLON] = ";";
	scancodeToKey[PNTR_APP_KEY_EQUAL] = "=";
	scancodeToKey[PNTR_APP_KEY_A] = "a";
	scancodeToKey[PNTR_APP_KEY_B] = "b";
	scancodeToKey[PNTR_APP_KEY_C] = "c";
	scancodeToKey[PNTR_APP_KEY_D] = "d";
	scancodeToKey[PNTR_APP_KEY_E] = "e";
	scancodeToKey[PNTR_APP_KEY_F] = "f";
	scancodeToKey[PNTR_APP_KEY_G] = "g";
	scancodeToKey[PNTR_APP_KEY_H] = "h";
	scancodeToKey[PNTR_APP_KEY_I] = "i";
	scancodeToKey[PNTR_APP_KEY_J] = "j";
	scancodeToKey[PNTR_APP_KEY_K] = "k";
	scancodeToKey[PNTR_APP_KEY_L] = "l";
	scancodeToKey[PNTR_APP_KEY_M] = "m";
	scancodeToKey[PNTR_APP_KEY_N] = "n";
	scancodeToKey[PNTR_APP_KEY_O] = "o";
	scancodeToKey[PNTR_APP_KEY_P] = "p";
	scancodeToKey[PNTR_APP_KEY_Q] = "q";
	scancodeToKey[PNTR_APP_KEY_R] = "r";
	scancodeToKey[PNTR_APP_KEY_S] = "s";
	scancodeToKey[PNTR_APP_KEY_T] = "t";
	scancodeToKey[PNTR_APP_KEY_U] = "u";
	scancodeToKey[PNTR_APP_KEY_V] = "v";
	scancodeToKey[PNTR_APP_KEY_W] = "w";
	scancodeToKey[PNTR_APP_KEY_X] = "x";
	scancodeToKey[PNTR_APP_KEY_Y] = "y";
	scancodeToKey[PNTR_APP_KEY_Z] = "z";
	scancodeToKey[PNTR_APP_KEY_LEFT_BRACKET] = "[";
	scancodeToKey[PNTR_APP_KEY_BACKSLASH] = "\\";
	scancodeToKey[PNTR_APP_KEY_RIGHT_BRACKET] = "]";
	scancodeToKey[PNTR_APP_KEY_GRAVE_ACCENT] = "`";
	scancodeToKey[PNTR_APP_KEY_WORLD_1] = "";
	scancodeToKey[PNTR_APP_KEY_WORLD_2] = "";
	scancodeToKey[PNTR_APP_KEY_ESCAPE] = "escape";
	scancodeToKey[PNTR_APP_KEY_ENTER] = "enter";
	scancodeToKey[PNTR_APP_KEY_TAB] = "tab";
	scancodeToKey[PNTR_APP_KEY_BACKSPACE] = "backspace";
	scancodeToKey[PNTR_APP_KEY_INSERT] = "insert";
	scancodeToKey[PNTR_APP_KEY_DELETE] = "delete";
	scancodeToKey[PNTR_APP_KEY_RIGHT] = "right";
	scancodeToKey[PNTR_APP_KEY_LEFT] = "left";
	scancodeToKey[PNTR_APP_KEY_DOWN] = "down";
	scancodeToKey[PNTR_APP_KEY_UP] = "up";
	scancodeToKey[PNTR_APP_KEY_PAGE_UP] = "pageup";
	scancodeToKey[PNTR_APP_KEY_PAGE_DOWN] = "pagedown";
	scancodeToKey[PNTR_APP_KEY_HOME] = "home";
	scancodeToKey[PNTR_APP_KEY_END] = "end";
	scancodeToKey[PNTR_APP_KEY_CAPS_LOCK] = "capslock";
	scancodeToKey[PNTR_APP_KEY_SCROLL_LOCK] = "scrolllock";
	scancodeToKey[PNTR_APP_KEY_NUM_LOCK] = "numlock";
	scancodeToKey[PNTR_APP_KEY_PRINT_SCREEN] = "printscreen";
	scancodeToKey[PNTR_APP_KEY_PAUSE] = "pause";
	scancodeToKey[PNTR_APP_KEY_F1] = "f1";
	scancodeToKey[PNTR_APP_KEY_F2] = "f2";
	scancodeToKey[PNTR_APP_KEY_F3] = "f3";
	scancodeToKey[PNTR_APP_KEY_F4] = "f4";
	scancodeToKey[PNTR_APP_KEY_F5] = "f5";
	scancodeToKey[PNTR_APP_KEY_F6] = "f6";
	scancodeToKey[PNTR_APP_KEY_F7] = "f7";
	scancodeToKey[PNTR_APP_KEY_F8] = "f8";
	scancodeToKey[PNTR_APP_KEY_F9] = "f9";
	scancodeToKey[PNTR_APP_KEY_F10] = "f10";
	scancodeToKey[PNTR_APP_KEY_F11] = "f11";
	scancodeToKey[PNTR_APP_KEY_F12] = "f12";
	scancodeToKey[PNTR_APP_KEY_F13] = "f13";
	scancodeToKey[PNTR_APP_KEY_F14] = "f14";
	scancodeToKey[PNTR_APP_KEY_F15] = "f15";
	scancodeToKey[PNTR_APP_KEY_F16] = "f16";
	scancodeToKey[PNTR_APP_KEY_F17] = "f17";
	scancodeToKey[PNTR_APP_KEY_F18] = "f18";
	scancodeToKey[PNTR_APP_KEY_F19] = "f19";
	scancodeToKey[PNTR_APP_KEY_F20] = "f20";
	scancodeToKey[PNTR_APP_KEY_F21] = "f21";
	scancodeToKey[PNTR_APP_KEY_F22] = "f22";
	scancodeToKey[PNTR_APP_KEY_F23] = "f23";
	scancodeToKey[PNTR_APP_KEY_F24] = "f24";
	scancodeToKey[PNTR_APP_KEY_F25] = "f25";
	scancodeToKey[PNTR_APP_KEY_KP_0] = "kp0";
	scancodeToKey[PNTR_APP_KEY_KP_1] = "kp1";
	scancodeToKey[PNTR_APP_KEY_KP_2] = "kp2";
	scancodeToKey[PNTR_APP_KEY_KP_3] = "kp3";
	scancodeToKey[PNTR_APP_KEY_KP_4] = "kp4";
	scancodeToKey[PNTR_APP_KEY_KP_5] = "kp5";
	scancodeToKey[PNTR_APP_KEY_KP_6] = "kp6";
	scancodeToKey[PNTR_APP_KEY_KP_7] = "kp7";
	scancodeToKey[PNTR_APP_KEY_KP_8] = "kp8";
	scancodeToKey[PNTR_APP_KEY_KP_9] = "kp9";
	scancodeToKey[PNTR_APP_KEY_KP_DECIMAL] = "kpdecimal";
	scancodeToKey[PNTR_APP_KEY_KP_DIVIDE] = "kpdivide";
	scancodeToKey[PNTR_APP_KEY_KP_MULTIPLY] = "kpmultiply";
	scancodeToKey[PNTR_APP_KEY_KP_SUBTRACT] = "kpsubtract";
	scancodeToKey[PNTR_APP_KEY_KP_ADD] = "kpadd";
	scancodeToKey[PNTR_APP_KEY_KP_ENTER] = "kpenter";
	scancodeToKey[PNTR_APP_KEY_KP_EQUAL] = "kpequal";
	scancodeToKey[PNTR_APP_KEY_LEFT_SHIFT] = "leftshift";
	scancodeToKey[PNTR_APP_KEY_LEFT_CONTROL] = "leftcontrol";
	scancodeToKey[PNTR_APP_KEY_LEFT_ALT] = "leftalt";
	scancodeToKey[PNTR_APP_KEY_LEFT_SUPER] = "leftsuper";
	scancodeToKey[PNTR_APP_KEY_RIGHT_SHIFT] = "rightshift";
	scancodeToKey[PNTR_APP_KEY_RIGHT_CONTROL] = "rightcontrol";
	scancodeToKey[PNTR_APP_KEY_RIGHT_ALT] = "rightalt";
	scancodeToKey[PNTR_APP_KEY_RIGHT_SUPER] = "rightsuper";
	scancodeToKey[PNTR_APP_KEY_MENU] = "menu";

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
