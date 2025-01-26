#ifndef SRC_LOVE_TYPES_GRAPHICS_COLOR_H_
#define SRC_LOVE_TYPES_GRAPHICS_COLOR_H_

#include "pntr_app.h"

namespace love {
namespace Types {
namespace Graphics {

/**
 * A color, holding red, green, blue and alpha values.
 */
struct Color {
	/**
	 * Create a color with the value of 0, 0, 0, 0.
	 */
	Color() : r(0), g(0), b(0), a(0) {
		// Nothing.
	}

	/**
	 * Create a new color.
	 */
	Color(int rValue, int gValue, int bValue, int aValue) : r(rValue), g(gValue), b(bValue), a(aValue) {
		// Nothing.
	}

	/**
	 * Create a new color.
	 */
	Color(int rValue, int gValue, int bValue) : r(rValue), g(gValue), b(bValue) {
		// Nothing.
	}

	Color(pntr_color color) {
		r = pntr_color_r(color);
		g = pntr_color_g(color);
		b = pntr_color_b(color);
		a = pntr_color_a(color);
	}

	pntr_color to_pntr_color();

	/**
	 * The amount of red.
	 */
	int r;

	/**
	 * The amount of green.
	 */
	int g;

	/**
	 * The amount of blue.
	 */
	int b;

	/**
	 * The amount of alpha.
	 */
	int a;
};

}  // namespace Graphics
}  // namespace Types
}  // namespace love

#endif  // SRC_LOVE_TYPES_GRAPHICS_COLOR_H_
