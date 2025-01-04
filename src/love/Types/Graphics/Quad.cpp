#include "Quad.h"
#include "pntr_app.h"

namespace love {
namespace Types {
namespace Graphics {

Quad::Quad(int t_x, int t_y, int t_width, int t_height, int t_sw, int t_sh)
	: x(t_x), y(t_y), width(t_width), height(t_height), sw(t_sw), sh(t_sh) {
	// Nothing.
}
Quad::Quad(int t_x, int t_y, int t_width, int t_height)
	: x(t_x), y(t_y), width(t_width), height(t_height) {
	// Nothing.
}

Quad::Quad() {
	// Nothing.
}

pntr_rectangle Quad::toRect() {
	pntr_rectangle rect;
	rect.x = x;
	rect.y = y;
	rect.width = width;
	rect.height = height;
	return rect;
}

}  // namespace Graphics
}  // namespace Types
}  // namespace love
