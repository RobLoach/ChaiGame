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
	if (ChaiLove::hasInstance()) {
		return ChaiLove::getInstance()->screen;
	}
	return NULL;
}

bool graphics::load() {
	// Enable alpha blending.
	// if (ChaiLove::getInstance()->config.options["alphablending"]) {
	// 	if (SDL_SetAlpha(getScreen(), SDL_SRCALPHA, 0) == -1) {
	// 		//LibretroLog::log(RETRO_LOG_ERROR) << "[ChaiLove] Enabling alpha blending failed" << std::endl;
	// 	}
	// }

	// Set the default font.
	graphics::setFont();
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
	if (image && image->loaded()) {
		// TODO: Implement rotozoomSurfaceXY

		// ChaiLove* app = ChaiLove::getInstance();
		// float angle = app->math.degrees(r);
		// SDL_Surface* tempSurface = rotozoomSurfaceXY(image->surface, angle, sx, sy, m_smooth);
		// if (tempSurface) {
		// 	float aspectX = ox / image->getWidth();
		// 	float aspectY = oy / image->getHeight();
		// 	SDL_Rect dstrect;
		// 	dstrect.x = x - aspectX * tempSurface->w;
		// 	dstrect.y = y - aspectY * tempSurface->h;
		// 	SDL_BlitSurface(tempSurface, NULL, getScreen(), &dstrect);
		// 	SDL_FreeSurface(tempSurface);
		// }
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
	return getScreen()->width;
}
int graphics::getHeight() {
	return getScreen()->height;
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
	return new Font(filename, glyphWidth, glyphHeight, letters);
}

Font* graphics::newFont(const std::string& filename, int size) {
	return new Font(filename, size);
}

Font* graphics::newFont(const std::string& filename) {
	return new Font(filename, 12);
}

Font* graphics::newFont() {
	return new Font();
}

graphics& graphics::setFont(Font* font) {
	activeFont = font;
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
