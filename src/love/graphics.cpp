#include "graphics.h"

#include "../ChaiLove.h"
#include "Types/Graphics/Image.h"
#include "Types/Graphics/Font.h"
#include "Types/Graphics/Color.h"

using love::Types::Graphics::Image;
using love::Types::Graphics::Quad;
using love::Types::Graphics::Font;
using love::Types::Graphics::Point;
using love::Types::Graphics::Color;

namespace love {

graphics::graphics() {
	setFont();
}

pntr_image* graphics::getScreen() {
	if (m_app != NULL) {
		return m_app->screen;
	}
	return NULL;
}

bool graphics::load(pntr_app* app) {
	// Set the default font.
	graphics::setFont();

	// Match the default colors of Love2D
	color_back = pntr_new_color(0, 0, 0, 255); // Black
	color_front = pntr_new_color(255, 255, 255, 255); // White

	m_app = app;

	return true;
}

graphics& graphics::clear() {
	pntr_clear_background(getScreen(), color_back);
	return *this;
}

graphics& graphics::clear(int r, int g, int b, int a) {
	pntr_clear_background(getScreen(), pntr_new_color(r, g, b, a));
	return *this;
}

graphics& graphics::clear(int r, int g, int b) {
	return clear(r, g, b, 255);
}

graphics& graphics::point(int x, int y) {
	pntr_draw_point(getScreen(), x, y, color_front);
	return *this;
}

graphics& graphics::point(Point* p) {
	return point(p->x, p->y);
}

/*
TODO: Fix graphics.points(Vector<Points>)
void graphics::points(std::vector<Point*> points) {
	for (std::vector<Point*>::iterator it = points.begin() ; it != points.end(); ++it) {
		point(*it);
	}
}
void graphics::points(std::vector<Point> points) {
	for (std::vector<Point>::iterator it = points.begin() ; it != points.end(); ++it) {
		Point a = *it;
		point(a.x, a.y);
	}
}
*/

graphics& graphics::rectangle(const std::string& drawmode, int x, int y, int width, int height) {
	if (drawmode == "line") {
		pntr_draw_rectangle(getScreen(), x, y, width, height, color_front);
	} else {
		pntr_draw_rectangle_fill(getScreen(), x, y, width, height, color_front);
	}

	return *this;
}

graphics& graphics::line(int x1, int y1, int x2, int y2) {
	pntr_draw_line(getScreen(), x1, y1, x2, y2, color_front);
	return *this;
}

graphics& graphics::draw(Image* image) {
	return draw(image, 0, 0);
}

graphics& graphics::draw(Image* image, int x, int y) {
	if (image && image->loaded()) {
		pntr_draw_image(getScreen(), image->surface, x, y);
	}

	return *this;
}

graphics& graphics::draw(Image* image, Quad quad) {
	return draw(image, quad, 0, 0);
}

graphics& graphics::draw(Image* image, Quad quad, int x, int y) {
	if (image && image->loaded()) {
		pntr_rectangle srcRect;
		srcRect.x = quad.x;
		srcRect.y = quad.x;
		srcRect.width = quad.sw;
		srcRect.height = quad.sh;
		pntr_draw_image_rec(getScreen(), image->surface, quad.toRect(), x, y);
	}

	return *this;
}

graphics& graphics::draw(Image* image, int x, int y, float r, float sx, float sy, float ox, float oy) {
	if (image == NULL) {
		return *this;
	}

	if (!image->loaded()) {
		return *this;
	}

	// TODO: Implement proper rotozoomSurfaceXY
	if (r == 0.0f) {
		pntr_draw_image_scaled(getScreen(), image->surface, x, y, sx, sy, ox, oy, m_smooth);
		return *this;
	}

	if (sx == 1.0f && sy == 1.0f) {
		ChaiLove* chailove = ChaiLove::getInstance();
		pntr_draw_image_rotated(getScreen(), image->surface, x, y, chailove->math.degrees(r), ox, oy, m_smooth);
		return *this;
	}

	pntr_image* scaled = pntr_image_scale(image->surface, sx, sy, m_smooth);
	if (scaled != NULL) {
		ChaiLove* chailove = ChaiLove::getInstance();
		pntr_draw_image_rotated(getScreen(), scaled, x, y, chailove->math.degrees(r), ox, oy, m_smooth);
		pntr_unload_image(scaled);
	}

	return *this;
}

graphics& graphics::draw(Image* image, int x, int y, float r, float sx, float sy, float ox) {
	return draw(image, x, y, r, sx, sy, ox, 0.0f);
}

graphics& graphics::draw(Image* image, int x, int y, float r, float sx, float sy) {
	return draw(image, x, y, r, sx, sy, 0.0f, 0.0f);
}

graphics& graphics::draw(Image* image, int x, int y, float r, float sx) {
	return draw(image, x, y, r, sx, sx, 0.0f, 0.0f);
}

graphics& graphics::draw(Image* image, int x, int y, float r) {
	if (r == 0.0f) {
		return draw(image, x, y);
	} else {
		return draw(image, x, y, r, 1.0f, 1.0f, 0.0f, 0.0f);
	}
}

Image* graphics::newImage(const std::string& filename) {
	return ChaiLove::getInstance()->image.newImageData(filename);
}

Quad graphics::newQuad(int x, int y, int width, int height, int sw, int sh) {
	return Quad(x, y, width, height, sw, sh);
}

graphics& graphics::print(const std::string& text) {
	activeFont->print(text, 0, 0, color_front);
	return *this;
}

graphics& graphics::print(const std::string& text, int x, int y) {
	activeFont->print(text, x, y, color_front);
	return *this;
}

graphics& graphics::setColor(int red, int green, int blue, int alpha) {
	color_front = pntr_new_color(red, green, blue, alpha);
	return *this;
}

graphics& graphics::setColor(int red, int green, int blue) {
	return setColor(red, green, blue, 255);
}

Color graphics::getColor() {
	return color_front;
}

Color graphics::getBackgroundColor() {
	return color_back;
}
graphics& graphics::setBackgroundColor(int red, int green, int blue) {
	return setBackgroundColor(red, green, blue, 255);
}
graphics& graphics::setBackgroundColor(int red, int green, int blue, int alpha) {
	color_back = pntr_new_color(red, green, blue, alpha);
	return *this;
}

/**
 * Sets the default scaling filters used with images, and fonts.
 */
graphics& graphics::setDefaultFilter(const std::string& filter) {
	if (filter == "linear") {
		m_smooth = PNTR_FILTER_BILINEAR;
	} else if (filter == "nearest") {
		m_smooth = PNTR_FILTER_NEARESTNEIGHBOR;
	}

	return *this;
}

/**
 * Returns the default scaling filters used with images and fonts.
 */
std::string graphics::getDefaultFilter() {
	switch (m_smooth) {
		case PNTR_FILTER_NEARESTNEIGHBOR:
			return "nearest";
		case PNTR_FILTER_BILINEAR:
			return "linear";
	}

	return "nearest";
}


int graphics::getWidth() {
	return pntr_app_width(m_app);
}
int graphics::getHeight() {
	return pntr_app_height(m_app);
}

Point graphics::getDimensions() {
	return Point(getWidth(), getHeight());
}

graphics& graphics::circle(const std::string& drawmode, int x, int y, int radius) {
	if (drawmode == "line") {
		pntr_draw_circle(getScreen(), x, y, radius, color_front);
	} else {
		pntr_draw_circle_fill(getScreen(), x, y, radius, color_front);
	}

	return *this;
}

graphics& graphics::arc(const std::string& drawmode, int x, int y, int radius, int angle1, int angle2) {
	if (drawmode == "line") {
		pntr_draw_arc(getScreen(), x, y, radius, angle1, angle2, radius * 2, color_front);
	} else {
		pntr_draw_arc_fill(getScreen(), x, y, radius, angle1, angle2, radius * 2, color_front);
	}

	return *this;
}

graphics& graphics::ellipse(const std::string& drawmode, int x, int y, int radiusx, int radiusy) {
	if (drawmode == "line") {
		pntr_draw_ellipse(getScreen(), x, y, radiusx, radiusy, color_front);
	} else {
		pntr_draw_ellipse_fill(getScreen(), x, y, radiusx, radiusy, color_front);
	}

	return *this;
}

Font* graphics::newFont(const std::string& filename, int glyphWidth, int glyphHeight, const std::string& letters) {
	Font* font = new Font(filename, glyphWidth, glyphHeight, letters);
	if (font->loaded()) {
		return font;
	}

	delete font;
	return NULL;
}

Font* graphics::newFont(const std::string& filename, int size) {
	Font* font = new Font(filename, size);
	if (font->loaded()) {
		return font;
	}

	delete font;
	return NULL;
}

Font* graphics::newFont(const std::string& filename) {
	Font* font = new Font(filename, 16);
	if (font->loaded()) {
		return font;
	}

	delete font;
	return NULL;
}

Font* graphics::newFont() {
	Font* font = new Font();
	if (font->loaded()) {
		return font;
	}

	delete font;
	return NULL;
}

Font* graphics::newFont(int size) {
	Font* font = new Font(size);
	if (font->loaded()) {
		return font;
	}

	delete font;
	return NULL;
}

graphics& graphics::setFont(Font* font) {
	if (font != NULL) {
		activeFont = font;
	}
	return *this;
}

graphics& graphics::setFont() {
	activeFont = &defaultFont;
	return *this;
}

Font* graphics::getFont() {
	return activeFont;
}

}  // namespace love
