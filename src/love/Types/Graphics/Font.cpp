#include "Font.h"
#include "pntr_app.h"
#include <string>
#include "../../../ChaiLove.h"
#include "Image.h"

namespace love {
namespace Types {
namespace Graphics {

Font::Font() {
	font = pntr_load_font_default();
}

Font::Font(const std::string& filename, int glyphWidth, int glyphHeight, const std::string& letters) {
	font = pntr_load_font_tty(filename.c_str(), glyphWidth, glyphHeight, letters.c_str());
}

Font::Font(const std::string& filename, int ptsize) {
	font = pntr_load_font_ttf(filename.c_str(), ptsize);
}

Font::~Font() {
	destroy();
}

bool Font::loaded() {
	return font != NULL;
}

bool Font::destroy() {
	if (font != NULL) {
		pntr_unload_font(font);
		font = NULL;
	}

	return true;
}

int Font::getHeight(const std::string& text) {
	pntr_vector size = pntr_measure_text_ex(font, text.c_str(), text.length());
	return size.y;
}

int Font::getHeight() {
	return getHeight("A");
}

int Font::getWidth(const std::string& text) {
	return pntr_measure_text(font, text.c_str());
}

void Font::print(const std::string& text, int x, int y, int r, int g, int b, int a) {
	pntr_image* screen = ChaiLove::getInstance()->screen;

	if (font == NULL || screen == NULL) {
		return;
	}

	pntr_color color = pntr_new_color((unsigned char)r, (unsigned char)g, (unsigned char)b, (unsigned char)a);
	pntr_draw_text(screen, font, text.c_str(), x, y, color);
}

void Font::print(const std::string& text, int x, int y, pntr_color color) {
	pntr_image* screen = ChaiLove::getInstance()->screen;

	if (font == NULL || screen == NULL) {
		return;
	}

	pntr_draw_text(screen, font, text.c_str(), x, y, color);
}

}  // namespace Graphics
}  // namespace Types
}  // namespace love
