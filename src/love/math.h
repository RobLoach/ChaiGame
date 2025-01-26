#ifndef SRC_LOVE_MATH_H_
#define SRC_LOVE_MATH_H_

#include <string>
#include "pntr_app.h"

namespace love {
/**
 * Provides system-independent mathematical functions.
 */
class math {
	public:
	bool load(pntr_app* app);

	/**
	 * Get uniformly distributed pseudo-random number, between the given numbers.
	 *
	 * @param min (0.0f) The minimum value.
	 * @param max (1.0f) The max value.
	 *
	 * @return A number between the two given min and max values.
	 *
	 * @code
	 * love.math.random(5, 10) // 5-10
	 * love.math.random(10)    // 0-10
	 * love.math.random()      // 0.0f-1.0f
	 * @endcode
	 */
	float random(float min, float max);
	float random(float max);
	float random();
	int random(int min, int max);
	int random(int max);
	double random(double min, double max);
	double random(double max);

	/**
	 * Sets the random seed to a random seed between the given min and max values.
	 *
	 * @param min The lower 32 bits of the seed value.
	 * @param max The higher 32 bits of the seed value.
	 *
	 * @return The math module, to allow for method chaining.
	 *
	 * @see love.math.getRandomSeed
	 */
	math& setRandomSeed(int min, int max);

	/**
	 * Sets the seed of the random number generator.
	 *
	 * @param seed The integer number with which you want to seed the randomization.
	 *
	 * @return The math module, to allow for method chaining.
	 *
	 * @see love.math.getRandomSeed
	 */
	math& setRandomSeed(int seed);

	/**
	 * Gets the seed of the random number generator.
	 *
	 * @see love.math.setRandomSeed
	 */
	int getRandomSeed();

	/**
	 * Converts from degrees to radians.
	 *
	 * @see love.math.degrees
	 */
	float rad(float degrees);

	/**
	 * Converts from radians to degrees.
	 *
	 * @see love.math.rad
	 */
	float degrees(float rad);

	/**
	 * Mathematic constant: e
	 *
	 * @see https://en.wikipedia.org/wiki/E_(mathematical_constant)
	 */
	const float e = 2.718281828459045f;

	/**
	 * Mathematics constant: Pi
	 *
	 * @see https://en.wikipedia.org/wiki/Pi
	 */
	const float pi = 3.14159265358979323846f;

	private:
	int m_seed = 0;

	pntr_app* app;
};

}  // namespace love

#endif  // SRC_LOVE_MATH_H_
