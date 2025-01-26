#include "system.h"
#include "../ChaiLove.h"

#include <string>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include "libretro.h"

namespace love {

system::system() {
	m_username = "";
}

std::string system::getOS() {
	// TODO(RobLoach): Replace Macros with something more complex?
	#if (defined __EMSCRIPTEN__)
	return "Web";
	#elif (defined __HAIKU__)
	return "Linux";
	#elif((defined __BEOS__) ||(defined __beos__))
	return "Linux";
	#elif(defined _WIN32_WCE) || (defined _WIN64_WCE)
	return "Windows";
	#elif((defined WINAPI_FAMILY) && WINAPI_FAMILY == WINAPI_FAMILY_APP)
	return "Windows";
	#elif(((defined _WIN32) || (defined _WIN64)) && (!defined __CYGWIN__))
	return "Windows";
	#elif(defined OS2)
	return "OS X";
	#elif((defined __MACH__) && (defined __APPLE__))
	return "OS X";
	#elif defined(macintosh)
	return "OS X";
	#elif defined(ANDROID)
	return "Android";
	#elif defined(__linux)
	return "Linux";
	#elif defined(__sun) || defined(sun)
	return "Linux";
	#elif defined(__FreeBSD__) || defined(__DragonFly__)
	return "Linux";
	#elif defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__)
	return "Linux";
	#elif defined(unix) || defined(__unix__)
	return "Linux";
	#else
	return "Other";
	#endif
}

std::vector<int> system::getVersion() {
	std::vector<int> version;
	version.push_back(CHAILOVE_VERSION_MAJOR);
	version.push_back(CHAILOVE_VERSION_MINOR);
	version.push_back(CHAILOVE_VERSION_PATCH);
	return version;
}

std::string system::getVersionString() {
	return CHAILOVE_VERSION_STRING;
}

void system::updateVariables(config& t) {
	// Update core option from the libretro variables.
	struct retro_variable var = {0};

	// Alpha Blending
	var.key = "chailove_alphablending";
	var.value = NULL;
	if (ChaiLove::environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value) {
		std::string varvalue(var.value);
		if (varvalue == "disabled") {
			t.options["alphablending"] = false;
		}
	}

	// High Quality
	var.key = "chailove_highquality";
	var.value = NULL;
	if (ChaiLove::environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value) {
		std::string varvalue(var.value);
		if (varvalue == "disabled") {
			t.options["highquality"] = false;
		}
	}
}

bool system::load(config& t) {
	// Ensure we retrieve the latest variable states.
	updateVariables(t);

	// Loading success.
	return true;
}

std::string system::getUsername() {
	if (!m_usernameInitialized) {
		m_usernameInitialized = true;
		const char *username = NULL;
		if (ChaiLove::environ_cb(RETRO_ENVIRONMENT_GET_USERNAME, &username) && username) {
			m_username = std::string(username);
		}
	}
	return m_username;
}

bool system::execute(const std::string& command) {
#ifdef CHAILOVE_DISABLE_LOVE_SYSTEM_EXECUTE
	pntr_app_log(PNTR_APP_LOG_ERROR, "[ChaiLove] [system] love.system.execute() is disabled");
	return false;
#else
	pntr_app_log_ex(PNTR_APP_LOG_INFO, "[ChaiLove] [system] love.system.execute: %s", command.c_str());
	int result = std::system(command.c_str());
	if (result != 0) {
		pntr_app_log(PNTR_APP_LOG_ERROR, "[ChaiLove] [system] love.system.execute failed");
		return false;
	}
	pntr_app_log(PNTR_APP_LOG_INFO, "[ChaiLove] [system] love.system.execute finished");
	return true;
#endif
}

std::string system::getClipboardText() {
	pntr_app* app = ChaiLove::getInstance()->app;

	return pntr_app_clipboard(app);
}

system& system::setClipboardText(const std::string& text) {
	pntr_app_set_clipboard(ChaiLove::getInstance()->app, text.c_str(), text.length());
	return *this;
}

}  // namespace love
