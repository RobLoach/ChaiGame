#ifndef SRC_LOVE_SCRIPT_H_
#define SRC_LOVE_SCRIPT_H_

#include <string>
#include <list>
#include "config.h"

#ifdef __HAVE_CHAISCRIPT__
#include <chaiscript/chaiscript.hpp>

// TODO(RobLoach): Fix Chai loading with the Standard Library.
// #include <chaiscript/chaiscript_stdlib.hpp>
#endif

namespace love {

/**
 * This module provides all the global functions and events that are called.
 *
 * The following `main.chai` is an example of some of these callbacks being used in unison.
 *
 * @code
 * global logo
 *
 * def load() {
 *   logo = love.graphics.newImage("logo.png")
 * }
 *
 * def draw() {
 *   love.graphics.print("Hello World!", 400, 300)
 *   love.graphics.draw(logo, 100, 100)
 * }
 *
 * def update(dt) {
 *   // Change something on the screen.
 * }
 * @endcode
 */
class script {
	public:
	script(const std::string& file);

	/**
	 * Modify some configuration options.
	 *
	 * @param t The config object to modify.
	 *
	 * This callback can live in the `conf.chai` file.
	 *
	 * ### Example
	 *
	 * @code
	 * def conf(t) {
	 *   // The ChaiLove version this game was made for.
	 *   t.version = "0.29.0"
	 *
	 *   // The width and height of the game.
	 *   t.window.width = 1024
	 *   t.window.height = 768
	 * }
	 * @endcode
	 *
	 * @see love.config
	 */
	void conf(config& t);

	/**
	 * This function is called exactly once at the beginning of the game.
	 *
	 * ### Example
	 *
	 * Establish some variables/resources on the game load, so that they can be used repeatedly in other functions (such as script::draw).
	 *
	 * @code
	 * global hamster
	 *
	 * def load() {
	 *   hamster = love.graphics.newImage("hamster.png")
	 * }
	 *
	 * def draw() {
	 *   love.graphics.draw(hamster, 100, 100)
	 * }
	 * @endcode
	 */
	void load();

	/**
	 * Callback function used to update the state of the game every frame.
	 *
	 * @param delta Time since the last update in seconds.
	 *
	 * ### Example
	 *
	 * Change a variable var at a constant rate (+/- 3 per second in this example).
	 *
	 * @code
	 * var position = 10
	 * var rate = 3
	 *
	 * def update(dt) {
	 *   if (love.keyboard.isDown("down")) {
	 *     position -= dt * rate
	 *   }
	 *   if (love.keyboard.isDown("up")) {
	 *     position += dt * rate
	 *   }
	 * }
	 * @endcode
	 */
	void update(float delta);

	/**
	 * Callback function used to draw on the screen every frame.
	 *
	 * ### Example
	 *
	 * Draw an image that was loaded in script::load (putting graphics.newImage in script::draw would cause the image to be reloaded every frame, which would cause issues).
	 *
	 * @code
	 * global hamster
	 *
	 * dev load() {
	 *   hamster = love.graphics.newImage("hamster.png")
	 * }
	 *
	 * def draw() {
	 *   love.graphics.draw(hamster, 100, 100)
	 * }
	 * @endcode
	 */
	void draw();

	/**
	 * Called when the game is requested to be reset.
	 *
	 * ### Example
	 *
	 * @code
	 * global textX = 10
	 *
	 * dev update(dt) {
	 *   textX += dt * 20
	 * }
	 *
	 * def draw() {
	 *   love.graphics.print("Hello World", textX, 100)
	 * }
	 *
	 * def reset() {
	 *   textX = 10
	 * }
	 * @endcode
	 */
	void reset();

	bool mainLoaded = false;

	bool loadModule(const std::string& moduleName);

	/**
	 * Called when a joystick button is pressed.
	 *
	 * @param joystick The joystick number.
	 * @param button The name of which button was released.
	 *
	 * ### Example
	 *
	 * @code
	 * global buttonPressed = ""
	 *
	 * def draw() {
	 *   love.graphics.print("Button Pressed: " + buttonPressed, 100, 100)
	 * }
	 *
	 * def joystickpressed(joy, button) {
	 *   buttonPressed = button
	 * }
	 * @endcode
	 *
	 * @see joystickreleased
	 */
	void joystickpressed(int joystick, const std::string& button);

	/**
	 * Called when a joystick button is released.
	 *
	 * @param joystick The joystick number.
	 * @param button The name of which button was released.
	 *
	 * ### Example
	 *
	 * @code
	 * global buttonReleased = ""
	 *
	 * def draw() {
	 *   love.graphics.print("Button Released: " + buttonReleased, 100, 100)
	 * }
	 *
	 * def joystickreleased(joy, button) {
	 *   buttonReleased = button
	 * }
	 * @endcode
	 *
	 * @see joystickpressed
	 */
	void joystickreleased(int joystick, const std::string& button);

	/**
	 * Called when a mouse button is pressed.
	 *
	 * @param x The mouse position on the x-axis.
	 * @param y The mouse position on the y-axis.
	 * @param button The mouse button name of which was pressed.
	 *
	 * ### Example
	 *
	 * @code
	 * global buttonPressed = "None"
	 * global mousex = 0
	 * global mousey = 0
	 *
	 * def draw() {
	 *   love.graphics.print("Mouse Button Pressed: " + buttonPressed, mousex, mousey)
	 * }
	 *
	 * def mousepressed(x, y, button) {
	 *   buttonPressed = button
	 *   mousex = x
	 *   mousey = y
	 * }
	 * @endcode
	 *
	 * @see mousereleased
	 */
	void mousepressed(int x, int y, const std::string& button);

	/**
	 * Called when a mouse button is released.
	 *
	 * @param x The mouse position on the x-axis.
	 * @param y The mouse position on the y-axis.
	 * @param button The mouse button name of which was released.
	 *
	 * ### Example
	 *
	 * @code
	 * global buttonReleased = "None"
	 * global mousex = 0
	 * global mousey = 0
	 *
	 * def draw() {
	 *   love.graphics.print("Mouse Button Released: " + buttonReleased, mousex, mousey)
	 * }
	 *
	 * def mousereleased(x, y, button) {
	 *   buttonReleased = button
	 *   mousex = x
	 *   mousey = y
	 * }
	 * @endcode
	 *
	 * @see mousepressed
	 */
	void mousereleased(int x, int y, const std::string& button);

	/**
	 * Called when the mouse is moved.
	 *
	 * @param x The mouse position on the x-axis.
	 * @param y The mouse position on the y-axis.
	 * @param dx The amount moved along the x-axis since the last time love.mousemoved was called.
	 * @param dy The amount moved along the y-axis since the last time love.mousemoved was called.
	 *
	 * ### Example
	 *
	 * @code
	 * global mousex = 0
	 * global mousey = 0
	 *
	 * def draw() {
	 *   love.graphics.setColor(255, 255, 255)
	 *   love.graphics.point(mousex, mousey)
	 * }
	 *
	 * def mousemoved(x, y, dx, dy) {
	 *   mousex = x
	 *   mousey = y
	 * }
	 * @endcode
	 */
	void mousemoved(int x, int y, int dx, int dy);

	/**
	 * Called when a key on the keyboard has been pressed.
	 *
	 * @param key The name of the key that was pressed.
	 * @param scancode The scancode of the key that was pressed.
	 *
	 * ### Example
	 *
	 * @code
	 * def keypressed(key, scancode) {
	 *     print("Key Pressed: " + key)
	 *     print("Scancode: " + to_string(scancode))
	 * }
	 * @endcode
	 *
	 * @see keyreleased
	 */
	void keypressed(const std::string& key, int scancode);

	/**
	 * Called when a key on the keyboard is released.
	 *
	 * @param key The name of the key that was released.
	 * @param scancode The scancode of the key that was released.
	 *
	 * ### Example
	 *
	 * @code
	 * def keyreleased(key, scancode) {
	 *     print("Key Released: " + key)
	 *     print("Scancode: " + to_string(scancode))
	 * }
	 * @endcode
	 *
	 * @see keypressed
	 */
	void keyreleased(const std::string& key, int scancode);

	/**
	 * Called when requested to save the current state.
	 *
	 * @return string A JSON array representing the current state.
	 *
	 * ### Example
	 *
	 * @code
	 * global score = 0
	 *
	 * def savestate() {
	 *     return to_json([
	 *         "score": score
	 *     ])
	 * }
	 * @endcode
	 *
	 * @see loadstate
	 */
	std::string savestate();

	/**
	 * Called when requested to load a state.
	 *
	 * @param data A JSON array representing the state to load.
	 *
	 * @return bool True if loading the state succeeded.
	 *
	 * ### Example
	 *
	 * @code
	 * global score = 0
	 *
	 * def loadstate(data) {
	 *     var info = from_json(data)
	 *     score = info["score"]
	 *     return true
	 * }
	 * @endcode
	 *
	 * @see savestate
	 */
	bool loadstate(const std::string& data);

	/**
	 * Called when requested to reset the state of all the cheats to their default state.
	 *
	 * ### Example
	 *
	 * @code
	 * global invincible = false
	 *
	 * def cheatreset() {
	 *     invincible = false
	 * }
	 * @endcode
	 *
	 * @see cheatset
	 */
	void cheatreset();

	/**
	 * Called when requested to enable or disable a cheat.
	 *
	 * @param index The index of the cheat.
	 * @param enabled Whether the cheat is to be enabled or disabled.
	 * @param code The code for the cheat.
	 *
	 * ### Example
	 *
	 * @code
	 * global invincible = false
	 *
	 * def cheatset(index, enabled, code) {
	 *     if (code == "invincible") {
	 *         // Enable or disable invincibility
	 *         invincible = enabled
	 *     }
	 * }
	 * @endcode
	 *
	 * @see cheatreset
	 */
	void cheatset(int index, bool enabled, const std::string& code);

	/**
	 * Callback function triggered when the game is closed.
	 *
	 * ### Example
	 *
	 * @code
	 * def exit() {
	 *     print("Thanks for playing. Please play again soon!")
	 * }
	 * @endcode
	 */
	void exit();

	chaiscript::Boxed_Value eval(const std::string& code, const std::string& filename);
	std::string evalString(const std::string& code, const std::string& filename);

	#ifdef __HAVE_CHAISCRIPT__
	chaiscript::ChaiScript chai;
	std::function<void()> chaiload;
	std::function<void(config&)> chaiconf;
	std::function<void(float)> chaiupdate;
	std::function<void()> chaidraw;
	std::function<void()> chaiexit;
	std::function<void()> chaireset;
	std::function<void(int, bool, const std::string&)> chaicheatset;
	std::function<void()> chaicheatreset;
	std::function<bool(const std::string&)> chailoadstate;
	std::function<std::string()> chaisavestate;
	std::function<void(int, const std::string&)> chaijoystickpressed;
	std::function<void(int, const std::string&)> chaijoystickreleased;
	std::function<void(int, int, const std::string&)> chaimousepressed;
	std::function<void(int, int, const std::string&)> chaimousereleased;
	std::function<void(int, int, int, int)> chaimousemoved;
	std::function<void(const std::string&, int)> chaikeypressed;
	std::function<void(const std::string&, int)> chaikeyreleased;
	bool hasUpdate = true;
	bool hasDraw = true;
	bool hasjoystickpressed = true;
	bool hasjoystickreleased = true;
	bool hasmousepressed = true;
	bool hasmousereleased = true;
	bool hasmousemoved = true;
	bool haskeypressed = true;
	bool haskeyreleased = true;
	bool hasexit = true;
	bool hasloadstate = true;
	bool hassavestate = true;
	bool hasload = true;
	bool hasconf = true;
	bool hasreset = true;
	bool hascheatreset = true;
	bool hascheatset = true;
	#endif

	std::string findModule(const std::string& filename);
	std::string replaceString(std::string subject, const std::string& search, const std::string& replace);
	bool require(const std::string& moduleName);

	// Properties
	std::list<std::string> m_requiremodules;
};

}  // namespace love

#endif  // SRC_LOVE_SCRIPT_H_
