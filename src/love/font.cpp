#include <string>
#include "pntr_app.h"
#include "font.h"
#include "Types/Graphics/Font.h"

namespace love {

font::~font() {
	unload();
}

bool font::load() {
	return true;
}

bool font::unload() {
	return true;
}

bool font::isOpen() {
	return true;
}

}  // namespace love
