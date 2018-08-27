#ifndef SRC_LOVE_FILESYSTEM_H_
#define SRC_LOVE_FILESYSTEM_H_

#include <string>
#include <vector>

#include "SDL.h"
#include "physfs.h"
#include "Types/FileSystem/FileInfo.h"

using love::Types::FileSystem::FileInfo;

namespace love {
/**
 * Provides an interface to the user's filesystem.
 */
class filesystem {
	public:
	/**
	 * Loads and runs a .chai file.
	 *
	 * @param file The name (and path) of the file. Having the .chai extension at the end is optional.
	 *
	 * ### Example
	 *
	 * @code
	 * love.filesystem.load("myscript.chai")
	 * love.filesystem.load("myotherscript")
	 * @endcode
	 *
	 * @return Whether or not the file was loaded and ran properly.
	 */
	bool load(const std::string& file);
	void mountlibretro();

	bool init(const std::string& file);
	bool unload();
	SDL_RWops* openRW(const std::string& filename);
	char* readChar(const std::string& filename);

	/**
	 * Read the contents of a file.
	 *
	 * @param file The name (and path) of the file.
	 *
	 * @return The contents of the file.
	 *
	 * @code
	 * var contents = love.filesystem.read("test.txt")
	 * print(contents)
	 * @endcode
	 */
	std::string read(const std::string& filename);

	/**
	 * Check whether a file or directory exists.
	 *
	 * @code
	 * if (love.filesystem.exists("test.txt")) {
	 *   print("The test.txt file exists")
	 * }
	 * else {
	 *   print("The test.txt file does not exist")
	 * }
	 * @endcode
	 */
	bool exists(const std::string& file);

	/**
	 * Get the size in bytes of a file.
	 *
	 * @param The file to get the size of.
	 *
	 * @return The size of the given file.
	 */
	int getSize(const std::string& file);

	/**
	 * Gets information about the specified file or directory.
	 *
	 * @param path The path of the file to get information for.
	 *
	 * @return A FileInfo object representing information about the path.
	 *
	 * @see love::Types::FileSystem::FileInfo
	 */
	FileInfo getInfo(const std::string& path);

	/**
	 * Unmounts a zip file or folder previously mounted with filesystem::unmount.
	 *
	 * @return bool True, when unmounting was a success.
	 */
	bool unmount(const std::string& archive);

	/**
	 * Mounts a zip file or folder in the game's save directory for reading.
	 *
	 * @return bool True, when mounting was a success.
	 */
	bool mount(const std::string& archive, const std::string& mountpoint);

	PHYSFS_sint64 getSize(PHYSFS_File* file);
	PHYSFS_file* openFile(const std::string& filename);

	/**
	 * Returns all files and subdirectories in the directory.
	 */
	std::vector<std::string> getDirectoryItems(const std::string& dir);

	/**
	 * Check whether something is a directory.
	 */
	bool isDirectory(const std::string& filename);

	/**
	 * Checks whether something is a file.
	 */
	bool isFile(const std::string& filename);

	/**
	 * Checks whether something is a symlink.
	 */
	bool isSymlink(const std::string& filename);

	/**
	 * Recursively creates a directory in the save directory.
	 *
	 * When called with "a/b" it creates both "a" and "a/b", if they don't exist already.
	 *
	 * @param name The directory to create.
	 *
	 * @return True if the directory was created, false otherwise.
	 */
	bool createDirectory(const std::string& name);

	/**
	 * Write data to a file in the save directory. If the file existed already, it will be completely replaced by the new contents.
	 *
	 * @param name The name (and path) of the file.
	 * @param data The string data to write to the file.
	 *
	 * @return True if the file was written, false otherwise.
	 */
	bool write(const std::string& name, const std::string& data);

	/**
	 * Iterate over the lines in a file, with the given delimiter.
	 *
	 * @param filename The file to load the lines from.
	 * @param delimiter ("\n") A string of characters representing what would be considered a new line.
	 *
	 * @return A vector array of strings representing all the lines in the given file.
	 */
	std::vector<std::string> lines(const std::string& filename, const std::string& delimiter);
	std::vector<std::string> lines(const std::string& filename);

	std::string getLastError();
};

}  // namespace love

#endif  // SRC_LOVE_FILESYSTEM_H_
