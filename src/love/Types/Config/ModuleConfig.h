#ifndef SRC_LOVE_TYPES_CONFIG_MODULECONFIG_H_
#define SRC_LOVE_TYPES_CONFIG_MODULECONFIG_H_

namespace love {
namespace Types {
namespace Config {

/**
 * Allows enabling or disiabling modules during initialization.
 *
 * @see https://love2d.org/wiki/Config_Files
 */
struct ModuleConfig {
	/**
	 * Enable or disable the sound module.
	 */
	bool sound = true;
};

}  // namespace Config
}  // namespace Types
}  // namespace love

#endif  // SRC_LOVE_TYPES_CONFIG_MODULECONFIG_H_
