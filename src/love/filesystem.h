#ifndef SRC_LOVE_FILESYSTEM_H_
#define SRC_LOVE_FILESYSTEM_H_

#include <string>
#include <vector>

#include "pntr_app.h"
#include "physfs.h"
#include "Types/FileSystem/FileInfo.h"
#include "Types/FileSystem/FileData.h"

using love::Types::FileSystem::FileInfo;
using love::Types::FileSystem::FileData;

namespace love {
/**
 * Provides an interface to the user's filesystem.
 */
class filesystem {
	public:
	/**
	 * Loads and runs a .chai file.
	 *
	 * ### Example
	 *
	 * @code
	 * love.filesystem.load("myscript.chai")
	 * love.filesystem.load("myotherscript")
	 * @endcode
	 *
	 * @param file The name (and path) of the file. Having the .chai extension at the end is optional.
	 *
	 * @return Whether or not the file was loaded and ran properly.
	 */
	bool load(const std::string& file);
	void mountlibretro();

	bool init(const std::string& file, const void* data, unsigned int dataSize);
	bool unload();
	void* openRW(const std::string& filename);
	char* readChar(const std::string& filename);

	/**
	 * Read the contents of a file.
	 *
	 * @param filename The name (and path) of the file.
	 *
	 * @return The contents of the file.
	 *
	 * @code
	 * var contents = love.filesystem.read("test.txt")
	 * print(contents)
	 * @endcode
	 */
	std::string read(const std::string& filename);
	void* readBuffer(const std::string& filename, int& size);

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
	 * @param file The file to get the size of.
	 *
	 * @return The size of the given file.
	 */
	int getSize(const std::string& file);

	std::string getFileExtension(const std::string& filepath);
	std::string getBasename(const std::string& filepath);
	std::string getParentDirectory(const std::string& filepath);

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
	 * Creates a new FileData from a file on the storage device.
	 *
	 * @param filepath Path to the file.
	 *
	 * @return The new FileData, or nil if an error occurred.
	 *
	 * @see love::Types::FileSystem::FileData
	 */
	FileData newFileData(const std::string& filepath);

	/**
	 * Creates a new FileData object.
	 *
	 * @param contents The contents fof the file.
	 * @param name The name of the file.
	 *
	 * @return Your new FileData.
	 *
	 * @see love::Types::FileSystem::FileData
	 */
	FileData newFileData(const std::string& contents, const std::string& name);

	/**
	 * Unmounts a zip file or folder previously mounted with love.filesystem.mount.
	 *
	 * @param archive The archive that was previously mounted with love.filesystem.mount.
	 *
	 * @return bool True, when unmounting was a success.
	 *
	 * @see mount
	 */
	bool unmount(const std::string& archive);

	/**
	 * Mounts a zip file or folder in the game's save directory for reading.
	 *
	 * @param archive The folder or zip file in the game's save directory to mount.
	 * @param mountpoint The new path the archive will be mounted to.
	 * @param appendToPath (true) Whether the archive will be searched when reading a filepath before or after already-mounted archives. This includes the game's source and save directories.
	 *
	 * @return bool True if the archive was successfully mounted, false otherwise.
	 *
	 * @see unmount
	 */
	bool mount(const std::string& archive, const std::string& mountpoint, bool appendToPath);
	bool mount(const std::string& archive, const std::string& mountpoint);
	bool mount(const char *archive, const std::string& mountpoint);
	bool mount(const void *data, unsigned int size, const std::string& mountpoint);

	/**
	 * Gets the path to the designated save directory.
	 *
	 * @return The path to the save directory.
	 */
	std::string getSaveDirectory();

	PHYSFS_sint64 getSize(PHYSFS_File* file);
	PHYSFS_file* openFile(const std::string& filename);

	/**
	 * Returns all files and subdirectories in the directory.
	 */
	std::vector<std::string> getDirectoryItems(const std::string& dir);

	/**
	 * Check whether something is a directory.
	 *
	 * @see isFile
	 * @see isSymlink
	 */
	bool isDirectory(const std::string& filename);

	/**
	 * Checks whether something is a file.
	 *
	 * @see isDirectory
	 * @see isSymlink
	 */
	bool isFile(const std::string& filename);

	/**
	 * Checks whether something is a symlink.
	 *
	 * @see isDirectory
	 * @see isFile
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
	 *
	 * @see read
	 */
	std::vector<std::string> lines(const std::string& filename, const std::string& delimiter);
	std::vector<std::string> lines(const std::string& filename);

	/**
	 * Get the path to the executable that was used to run this application.
	 *
	 * @return The base path of the application.
	 */
	std::string getExecutablePath();

	std::string getLastError();
};

}  // namespace love

#endif  // SRC_LOVE_FILESYSTEM_H_
