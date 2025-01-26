#ifndef SRC_LOVE_WINDOW_H_
#define SRC_LOVE_WINDOW_H_

#include <string>
#include "config.h"
#include "pntr_app.h"
#include "Types/Graphics/Point.h"

using love::Types::Graphics::Point;

namespace love {

/**
 * Provides an interface for modifying and retrieving information about the program's window.
 */
class window {
	public:
	/**
	 * Gets the window title.
	 *
	 * @return The current window title.
	 *
	 * @see love.window.setTitle
	 */
	std::string getTitle();

	/**
	 * Sets the window title.
	 *
	 * @param title The new window title.
	 *
	 * @return The window system, for method chaining.
	 *
	 * @see love.window.getTitle
	 */
	window& setTitle(const std::string& title);

	/**
	 * Display a simple message for a certain amount of frames.
	 *
	 * @param msg The message text to be displayed.
	 * @param frames (2800) The amount of frames to display the message.
	 *
	 * @return The window system, for method chaining.
	 */
	window& showMessageBox(const std::string& msg, int frames);
	window& showMessageBox(const std::string& msg);

	bool load(pntr_app* app, const config& conf);
	bool unload();

	pntr_app* m_app;
};

}  // namespace love

#endif  // SRC_LOVE_WINDOW_H_
