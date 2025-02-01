#ifndef SRC_LOVE_TIMER_H_
#define SRC_LOVE_TIMER_H_

#include "pntr_app.h"

namespace love {

/**
 * Provides high-resolution timing functionality.
 */
class timer {
	public:
	void load(pntr_app* app);
	float step(float delta);

	/**
	 * Returns the time between the last two frames.
	 *
	 * @return The time passed (in seconds).
	 */
	float getDelta();

	/**
	 * Returns the current frames per second.
	 *
	 * @return The current FPS.
	 *
	 * @code
	 * var fps = love.timer.getFPS()
	 * print("FPS: " + to_string(fps))
	 * @endcode
	 */
	int getFPS();
	pntr_app* m_app;
};

}  // namespace love

#endif  // SRC_LOVE_TIMER_H_
