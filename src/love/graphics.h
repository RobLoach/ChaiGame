#ifndef SRC_LOVE_GRAPHICS_H_
#define SRC_LOVE_GRAPHICS_H_

#include <vector>

#include "pntr_app.h"
#include "Types/Graphics/Image.h"
#include "Types/Graphics/Quad.h"
#include "Types/Graphics/Font.h"
#include "Types/Graphics/Point.h"
#include "Types/Graphics/Color.h"

using love::Types::Graphics::Image;
using love::Types::Graphics::Quad;
using love::Types::Graphics::Font;
using love::Types::Graphics::Point;
using love::Types::Graphics::Color;

namespace love {

/**
 * The primary purpose of the graphics module is to draw to the screen.
 */
class graphics {
	public:
	graphics();
	bool load();

	/**
	 * Draws a rectangle.
	 *
	 * @param drawmode How to draw the rectangle. Can be "fill" or "line".
	 * @param x The position of top-left corner along the x-axis.
	 * @param y The position of top-left corner along the y-axis.
	 * @param width Width of the rectangle.
	 * @param height Height of the rectangle.
	 *
	 * @code
	 * love.graphics.rectangle("fill", 100, 100, 50, 50)
	 * @endcode
	 */
	graphics& rectangle(const std::string& drawmode, int x, int y, int width, int height);

	/**
	 * Clears the screen to the set background color.
	 */
	graphics& clear();

	/**
	 * Clears the screen to the given background color.
	 *
	 * @param r Red value.
	 * @param g Green value.
	 * @param b Blue value.
	 * @param a (255) Alpha value.
	 */
	graphics& clear(int r, int g, int b, int a);
	graphics& clear(int r, int g, int b);

	/**
	 * Draws a point.
	 *
	 * @param x The position on the x-axis.
	 * @param y The position on the y-axis.
	 */
	graphics& point(int x, int y);

	/**
	 * Draws a point.
	 *
	 * @param p The point to draw on the screen.
	 */
	graphics& point(Point* p);

	// void points(std::vector<Point*>);
	// void points(std::vector<Point>);

	/**
	 * Draws a line.
	 *
	 * @param x1 The position of first point on the x-axis.
	 * @param y1 The position of first point on the y-axis.
	 * @param x2 The position of second point on the x-axis.
	 * @param y2 The position of second point on the y-axis.
	 */
	graphics& line(int x1, int y1, int x2, int y2);

	/**
	 * Creates a new Quad.
	 */
	Quad newQuad(int x, int y, int width, int height, int sw, int sh);

	/**
	 * Creates a new Image from a given filepath.
	 *
	 * @param filename The filepath to the image file.
	 *
	 * @return An image object which can be drawn to the screen.
	 *
	 * @code
	 * var logo = love.graphics.newImage("logo.png")
	 * @endcode
	 */
	Image* newImage(const std::string& filename);


	/**
	 * Creates a new TrueType font, with the given font size.
	 *
	 * @param filename (default) The path to the TrueType .ttf font. When not provided, will return the default font.
	 * @param size (12) The size of the font to create.
	 *
	 * @return The created TrueType font.
	 */
	Font* newFont(const std::string& filename, int size);
	Font* newFont(const std::string& filename);
	Font* newFont();

	/**
	 * Creates a new BMFont with the given spec.
	 *
	 * @param filename The path to the font image.
	 * @param glyphWidth The width of each character.
	 * @param glyphHeight The height of each character.
	 * @param letters The letters presented in the font image.
	 *
	 * @return The created BMFont.
	 */
	Font* newFont(const std::string& filename, int glyphWidth, int glyphHeight, const std::string& letters);

	/**
	 * Set an already-loaded Font as the current font.
	 *
	 * @param (font) The font to set as the active font. When not provided will set the default font.
	 *
	 * @see getFont
	 */
	graphics& setFont(Font* font);
	graphics& setFont();

	/**
	 * Retrieve th currently active font.
	 *
	 * @see setFont
	 */
	Font* getFont();

	/**
	 * Prints the given text to the screen.
	 *
	 * @param text The text to draw.
	 * @param x (0) The position to draw the object (x-axis).
	 * @param y (0) The position to draw the object (y-axis).
	 *
	 * @code
	 * love.graphics.print("Hello World", 100, 100)
	 * @endcode
	 */
	graphics& print(const std::string& text, int x, int y);
	graphics& print(const std::string& text);

	/**
	 * Sets the active drawing color to the given color.
	 *
	 * @param red The amount of red.
	 * @param green The amount of green.
	 * @param blue The amount of blue.
	 * @param alpha (255) The amount of alpha.
	 *
	 * @see getColor
	 */
	graphics& setColor(int red, int green, int blue, int alpha);
	graphics& setColor(int red, int green, int blue);

	/**
	 * Gets the current color.
	 *
	 * @return The active color.
	 */
	Color getColor();

	/**
	 * Retrieves the active background color.
	 *
	 * @see love.graphics.setBackgroundColor
	 */
	Color getBackgroundColor();

	/**
	 * Sets the background color to the given color.
	 *
	 * @param red The r value.
	 * @param green The g value.
	 * @param blue The b value.
	 * @param alpha (255) The a value.
	 *
	 * @see love.graphics.getBackgroundColor
	 */
	graphics& setBackgroundColor(int red, int green, int blue, int alpha);
	graphics& setBackgroundColor(int red, int green, int blue);

	/**
	 * Sets the default scaling filters used with images, and fonts.
	 *
	 * @param filter The filter mode to apply when rotating or scaling graphics. This can be either "linear" (default), or "nearest".
	 *
	 * @see love.graphics.getDefaultFilter
	 * @see https://love2d.org/wiki/FilterMode
	 */
	graphics& setDefaultFilter(const std::string& filter);

	/**
	 * Returns the default scaling filters used with images and fonts.
	 *
	 * @see love.graphics.setDefaultFilter
	 */
	std::string getDefaultFilter();

	/**
	 * Retrieve the width of the screen.
	 */
	int getWidth();

	/**
	 * Retrieve the height of the screen.
	 */
	int getHeight();

	/**
	 * Gets the width and height of the window.
	 *
	 * @see love.graphics.getWidth
	 * @see love.graphics.getHeight
	 *
	 * @return A Point refering the x and y size of the window.
	 */
	Point getDimensions();

	/**
	 * Draws a circle.
	 *
	 * @param drawmode How to draw the circle. Can be "fill" or "line".
	 * @param x The position of the center along x-axis.
	 * @param y The position of the center along y-axis.
	 * @param radius The radius of the circle.
	 */
	graphics& circle(const std::string& drawmode, int x, int y, int radius);

	/**
	 * Draws an ellipse.
	 *
	 * @param drawmode How to draw the ellipse. Can be "fill" or "line".
	 * @param x The position of the center along x-axis.
	 * @param y The position of the center along y-axis.
	 * @param radiusx The radius of the ellipse along the x-axis (half the ellipse's width).
	 * @param radiusy The radius of the ellipse along the y-axis (half the ellipse's height).
	 */
	graphics& ellipse(const std::string& drawmode, int x, int y, int radiusx, int radiusy);

	/**
	 * Draws an image with the given angle, zoom, and origin.
	 *
	 * @param image The image to draw on the screen.
	 * @param x (0) The position to draw the object (x-axis).
	 * @param y (0) The position to draw the object (y-axis).
	 * @param r (0) Orientation (radians).
	 * @param sx (1) Scale factor (x-axis).
	 * @param sy (sx) Scale factor (y-axis).
	 * @param ox (0) Origin offset (x-axis).
	 * @param oy (0) Origin offset (y-axis).
	 */
	graphics& draw(Image* image, int x, int y, float r, float sx, float sy, float ox, float oy);
	graphics& draw(Image* image, int x, int y, float r, float sx, float sy, float ox);
	graphics& draw(Image* image, int x, int y, float r, float sx, float sy);
	graphics& draw(Image* image, int x, int y, float r, float sx);
	graphics& draw(Image* image, int x, int y, float r);
	graphics& draw(Image* image, int x, int y);
	graphics& draw(Image* image);

	/**
	 * Draws an image on screen, using the given Quad as a source.
	 *
	 * @param image The image to draw on the screen.
	 * @param quad The source quad of the image.
	 * @param x (0) The position to draw the object (x-axis).
	 * @param y (0) The position to draw the object (y-axis).
	 */
	graphics& draw(Image* image, Quad quad, int x, int y);
	graphics& draw(Image* image, Quad quad);

	/**
	 * Draws an arc.
	 *
	 * @param drawmode How to draw the arc. Can be "fill" or "line".
	 * @param x The position to draw the object (x-axis).
	 * @param y The position to draw the object (y-axis).
	 * @param radius The radius of the arc.
	 * @param angle1 The angle of the first
	 * @param angle2 The angle of the second.
	 */
	graphics& arc(const std::string& drawmode, int x, int y, int radius, int angle1, int angle2);

	pntr_color color_front;
	pntr_color color_back;

	pntr_image* getScreen();
	Font* activeFont = NULL;
	Font defaultFont;

	int m_smooth = 1;
};

}  // namespace love

#endif  // SRC_LOVE_GRAPHICS_H_
