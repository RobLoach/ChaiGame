#include "Color.h"

namespace love {
namespace Types {
namespace Graphics {

pntr_color Color::to_pntr_color() {
    return pntr_new_color(r, g, b, a);
}

}  // namespace Graphics
}  // namespace Types
}  // namespace love
