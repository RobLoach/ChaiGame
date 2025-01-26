#ifndef SRC_LOVE_TYPES_GRAPHICS_IMAGE_H_
#define SRC_LOVE_TYPES_GRAPHICS_IMAGE_H_

#include "pntr.h"
#include <string>

namespace love {
namespace Types {
namespace Graphics {

/**
 * Drawable image type.
 *
 * @see love.graphics.newImage
 */
class Image {
	public:
	pntr_image* surface;
	Image(const unsigned char* data, unsigned int size);
	Image(const std::string& filename);
	~Image();
	bool loaded();
	bool loadFromRW(const unsigned char* data, unsigned int size);
	bool destroy();

	/**
	 * Gets the width of the Texture.
	 *
	 * @see getHeight
	 */
	int getWidth();

	/**
	 * Gets the height of the Texture.
	 *
	 * @see getWidth
	 */
	int getHeight();
};

}  // namespace Graphics
}  // namespace Types
}  // namespace love

#endif  // SRC_LOVE_TYPES_GRAPHICS_IMAGE_H_
