#ifndef SRC_LOVE_TYPES_GRAPHICS_FONT_H_
#define SRC_LOVE_TYPES_GRAPHICS_FONT_H_

#include "pntr_app.h"
#include "pntr.h"
#include <string>
#include "Image.h"

namespace love {
namespace Types {
namespace Graphics {

/**
 * Defines the shape of characters that can be drawn onto the screen.
 */
class Font {
	public:
	Font();
	Font(const std::string& filename, int glyphWidth, int glyphHeight, const std::string& letters);
	Font(const std::string& filename, int ptsize);
	~Font();

	/**
	 * Retrieves whether or not the font is loaded.
	 */
	bool loaded();
	bool destroy();
	void print(const std::string& text, int x, int y, int r, int g, int b, int a);
	void print(const std::string& text, int x, int y, pntr_color color);
	pntr_font* font = NULL;

	/**
	 * Determines the vertical size the given text needs.
	 */
	int getHeight(const std::string& text);

	/**
	 * Determines the vertical size a line of text needs.
	 */
	int getHeight();

	/**
	 * Determines the horizontal size a line of text needs.
	 */
	int getWidth(const std::string& text);
};

}  // namespace Graphics
}  // namespace Types
}  // namespace love

#endif  // SRC_LOVE_TYPES_GRAPHICS_FONT_H_
