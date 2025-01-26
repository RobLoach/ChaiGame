#include "event.h"

#include "../ChaiLove.h"

namespace love {

void event::quit() {
	m_shouldclose = true;
}

void event::update() {
}

}  // namespace love
