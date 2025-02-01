#include "timer.h"

namespace love {

void timer::load(pntr_app* app) {
	// Nothing.
	m_app = app;
}

float timer::getDelta() {
	return pntr_app_delta_time(m_app);
}

float timer::step(float delta) {
	return delta;
}

int timer::getFPS() {
	return pntr_app_fps(m_app);
}

}  // namespace love
