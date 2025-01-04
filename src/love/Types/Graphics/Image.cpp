#include "Image.h"
#include "pntr.h"

#include <string>
#include "../../../ChaiLove.h"

namespace love {
namespace Types {
namespace Graphics {

Image::Image(const unsigned char* data, unsigned int size) {
	loadFromRW(data, size);
}

bool Image::loaded() {
	return surface != NULL;
}

bool Image::loadFromRW(const unsigned char* data, unsigned int size) {
	surface = pntr_load_image_from_memory(PNTR_IMAGE_TYPE_PNG, data, size);

	if (!loaded()) {
		const char* errorChar = pntr_get_error();
		std::string errString("");
		if (errorChar != NULL) {
			errString = errorChar;
		}
		//LibretroLog::log(RETRO_LOG_ERROR) << "STBIMG_Load_RW failed to load data: " << errString << std::endl;
		return false;
	}

	return true;
}

bool Image::destroy() {
	if (loaded()) {
		pntr_unload_image(surface);
		surface = NULL;
	}
	return true;
}

Image::~Image() {
	destroy();
}

Image::Image(const std::string& filename) {
	surface = pntr_load_image(filename.c_str());
}

int Image::getWidth() {
	if (loaded()) {
		return surface->width;
	}
	return 0;
}

int Image::getHeight() {
	if (loaded()) {
		return surface->height;
	}
	return 0;
}

}  // namespace Graphics
}  // namespace Types
}  // namespace love
