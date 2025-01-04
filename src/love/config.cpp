#include "config.h"
#include "../ChaiLove.h"

namespace love {

config::config() {
	options["alphablending"] = true;
	options["highquality"] = true;
	version = CHAILOVE_VERSION_STRING;
}

}  // namespace love
