#ifndef SRC_LOVE_TYPES_GRAPHICS_QUAD_H_
#define SRC_LOVE_TYPES_GRAPHICS_QUAD_H_

#include "pntr_app.h"

namespace love {
namespace Types {
namespace Graphics {

/**
 * An x, y, width, height, source width and source height.
 */
class Quad {
	public:
	/**
	 * The x coordinate.
	 */
	int x;

	/**
	 * The y coordinate.
	 */
	int y;

	/**
	 * The width of the Quad.
	 */
	int width;

	/**
	 * The height of the Quad.
	 */
	int height;

	int sw;
	int sh;
	Quad();
	Quad(int x, int y, int width, int height, int sw, int sh);
	Quad(int x, int y, int width, int height);
	pntr_rectangle toRect();
};

}  // namespace Graphics
}  // namespace Types
}  // namespace love

#endif  // SRC_LOVE_TYPES_GRAPHICS_QUAD_H_
