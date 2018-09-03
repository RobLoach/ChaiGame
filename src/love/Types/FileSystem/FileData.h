#ifndef SRC_LOVE_TYPES_FILESYSTEM_FILEDATA_H_
#define SRC_LOVE_TYPES_FILESYSTEM_FILEDATA_H_

#include <string>

namespace love {
namespace Types {
namespace FileSystem {

/**
 * Information about a file.
 *
 * @see love.filesystem.newFileData
 */
class FileData {
	public:
	/**
	 * Creates a new FileData from a file on the storage device.
	 *
	 * @param filepath Path to the file.
	 */
	FileData(const std::string& filepath);

	/**
	 * The size of the Data in bytes.
	 */
	int getSize();

	/**
	 * Gets the filename of the FileData.
	 */
	std::string getFilename();

	/**
	 * Gets the full Data as a string.
	 */
	std::string getString();

	/**
	 * Gets the extension of the FileData.
	 */
	std::string getExtension();

	std::string m_filepath;
};

}  // namespace FileSystem
}  // namespace Types
}  // namespace love

#endif  // SRC_LOVE_TYPES_FILESYSTEM_FILEDATA_H_
