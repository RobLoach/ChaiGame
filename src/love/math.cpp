#include "math.h"

namespace love {

bool math::load(pntr_app* application) {
	app = application;
	return true;
}

float math::random() {
	return random(0.0f, 1.0f);
}

float math::random(float max) {
	return random(0.0f, max);
}

float math::random(float min, float max) {
	return pntr_app_random_float(app, min, max);
}

int math::random(int max) {
	return random(0, max);
}

int math::random(int min, int max) {
	return pntr_app_random(app, min, max);
}

double math::random(double min, double max) {
	return (double)pntr_app_random_float(app, (float)min, (float)max);
}

double math::random(double max) {
	return (double)pntr_app_random_float(app, 0.0f, (float)max);
}

math& math::setRandomSeed(int min, int max) {
	return setRandomSeed(random(min, max));
}

math& math::setRandomSeed(int seed) {
	pntr_app_random_set_seed(app, seed);
	return *this;
}

int math::getRandomSeed() {
	return (int)pntr_app_random_seed(app);
}

float math::rad(float degress) {
	return degress * pi / 180.0f;
}

float math::degrees(float rad) {
	return rad * 180.0f / pi;
}

}  // namespace love
