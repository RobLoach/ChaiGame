#include <string>

#include "libretro.h"
#include "physfs.h"
#include "filesystem.h"
#include "../ChaiLove.h"
#include "Types/FileSystem/FileInfo.h"

using love::Types::FileSystem::FileInfo;
using love::Types::FileSystem::FileData;

namespace love {

/**
 * Initialize the file system.
 */
bool filesystem::init(const std::string& file, const void* data, unsigned int dataSize) {
	// Check if we are simply running ChaiLove.
	if (file.empty()) {
		return mount(".", "/", false);
	}

	// Find the parent and extension of the given file.
	std::string extension(getFileExtension(file));

	// Allow loading from an Archive.
	if (extension == "chaigame" || extension == "chailove" || extension == "zip") {
		return mount(data, dataSize, "/");
	}

	// If we are just running the core, load the base path.
	std::string parentPath(getParentDirectory(file));
	if (parentPath.empty()) {
		return mount(".", "/", false);
	}

	// Otherwise, we are loading a .chai file directly. Load it.
	return mount(parentPath.c_str(), "/", false);
}

std::string filesystem::getParentDirectory(const std::string& filepath) {
	size_t last = filepath.find_last_of("/\\");
	if (last != std::string::npos) {
		return filepath.substr(0, last);
	}
	return "";
}

std::string filesystem::getFileExtension(const std::string& filepath) {
	size_t i = filepath.rfind('.', filepath.length());
	if (i != std::string::npos) {
		return filepath.substr(i + 1, filepath.length() - i);
	}
	return "";
}

std::string filesystem::getBasename(const std::string& filepath) {
	char sep = '/';
	if (filepath.find('\\') != std::string::npos) {
		sep = '\\';
	}

	size_t i = filepath.rfind(sep, filepath.length());
	if (i != std::string::npos) {
		return filepath.substr(i + 1, filepath.length() - i);
	}

	return filepath;
}

void filesystem::mountlibretro() {
	// Mount some of the libretro directories.
	const char *system_dir = NULL;
	const char *assets_dir = NULL;
	const char *save_dir = NULL;
	const char *core_dir = NULL;

	if (ChaiLove::environ_cb(RETRO_ENVIRONMENT_GET_LIBRETRO_PATH, &core_dir) && core_dir) {
		// Make sure to get the directory of the core.
		std::string parentPath(getParentDirectory(core_dir));
		mount(parentPath, "/libretro/core", false);
	}
	if (ChaiLove::environ_cb(RETRO_ENVIRONMENT_GET_SYSTEM_DIRECTORY, &system_dir) && system_dir) {
		mount(system_dir, "/libretro/system", false);
	}
	if (ChaiLove::environ_cb(RETRO_ENVIRONMENT_GET_CORE_ASSETS_DIRECTORY, &assets_dir) && assets_dir) {
		mount(assets_dir, "/libretro/assets", false);
	}
	if (ChaiLove::environ_cb(RETRO_ENVIRONMENT_GET_SAVE_DIRECTORY, &save_dir) && save_dir) {
		save_dir = *save_dir ? save_dir : system_dir;
		mount(save_dir, "/libretro/saves", false);
	} else if (system_dir) {
		// Have the system directory be the save directory if available.
		mount(save_dir = system_dir, "/libretro/saves", false);
	} else {
		// Save directory becomes the current working directory.
		mount(save_dir = ".", "/libretro/saves", false);
	}

	// Ensure the write directory is set to the Save Directory.
	PHYSFS_setWriteDir(save_dir);
}

bool filesystem::load(const std::string& file) {
	return ChaiLove::getInstance()->script->loadModule(file);
}

bool filesystem::exists(const std::string& file) {
	return PHYSFS_exists(file.c_str()) != 0;
}

int filesystem::getSize(const std::string& file) {
	PHYSFS_File* openfile = PHYSFS_openRead(file.c_str());
	PHYSFS_sint64 size = -1;
	if (openfile) {
		size = getSize(openfile);
		PHYSFS_close(openfile);
	}
	return static_cast<int>(size);
}

PHYSFS_sint64 filesystem::getSize(PHYSFS_File* file) {
	PHYSFS_sint64 size = -1;
	if (file) {
		size = PHYSFS_fileLength(file);
		if (size < 0) {
			//LibretroLog::log(RETRO_LOG_ERROR) << "[ChaiLove] [filesystem] Could not get size of file " << getLastError() << std::endl;
			return -1;
		}
	} else {
		//LibretroLog::log(RETRO_LOG_ERROR) << "[ChaiLove] [filesystem] The file is not currently open." << std::endl;
	}
	return size;
}

bool filesystem::unload() {
	return true;
}

void* filesystem::openRW(const std::string& filename) {
	unsigned int size;
	void* data = pntr_load_file(filename.c_str(), &size);
	if (data == NULL) {
		//LibretroLog::log(RETRO_LOG_ERROR) << "[ChaiLove] [filesystem] Error loading file " << filename << getLastError() << std::endl;
	}
	return data;
}

PHYSFS_file* filesystem::openFile(const std::string& filename) {
	PHYSFS_file* myfile = PHYSFS_openRead(filename.c_str());
	if (myfile == NULL) {
		//LibretroLog::log(RETRO_LOG_ERROR) << "[ChaiLove] [filesystem] Error opening file " << filename << getLastError() << std::endl;
		return NULL;
	}
	return myfile;
}

char* filesystem::readChar(const std::string& filename) {
	char* output = NULL;
	PHYSFS_file* myfile = openFile(filename);
	if (myfile == NULL) {
		return NULL;
	}

	PHYSFS_sint64 file_size = getSize(myfile);
	if (file_size > 0) {
		output = new char[file_size + 1];
		int length_read = PHYSFS_readBytes(myfile, output, file_size);
		if (length_read != file_size) {
			//LibretroLog::log(RETRO_LOG_ERROR) << "[ChaiLove] [filesystem] File System error while reading from file " << filename << getLastError() << std::endl;
			output = NULL;
		} else {
			// Make sure there is a null terminating character at the end of the string.
			output[file_size] = '\0';
		}
	} else {
		//LibretroLog::log(RETRO_LOG_ERROR) << "[ChaiLove] [filesystem] Error getting filesize of " << filename << getLastError() << std::endl;
	}

	PHYSFS_close(myfile);
	return output;
}

std::string filesystem::read(const std::string& filename) {
	// Retrieve a character buffer.
	char* myBuf = readChar(filename);
	std::string output;
	if (myBuf != NULL) {
		output = std::string(myBuf);
	}
	return output;
}

void* filesystem::readBuffer(const std::string& filename, int& size) {
	PHYSFS_file* file = openFile(filename);
	if (file == NULL) {
		return NULL;
	}

	// Find the file size.
	size = getSize(file);
	if (size <= 0) {
		PHYSFS_close(file);
		return NULL;
	}

	// Create the buffer.
	void* buffer = (void*)malloc(size + 1);
	if (!buffer) {
		//LibretroLog::log(RETRO_LOG_ERROR) << "[ChaiLove] [filesystem] Failed to allocate buffer of size " << size + 1 << "." << std::endl;
		PHYSFS_close(file);
		return NULL;
	}

	// Read the file into the buffer.
	int result = PHYSFS_readBytes(file, buffer, size);
	if (result < 0) {
		//LibretroLog::log(RETRO_LOG_ERROR) << "[ChaiLove] [filesystem] Failed to load SoundData " << filename << getLastError() << std::endl;
		free(buffer);
		PHYSFS_close(file);
		return NULL;
	}

	PHYSFS_close(file);
	return buffer;
}

bool filesystem::unmount(const std::string& archive) {
	//LibretroLog::log(RETRO_LOG_INFO) << "[filesystem] Unmounting " << archive << std::endl;
	int returnValue = PHYSFS_unmount(archive.c_str());
	if (returnValue == 0) {
		//LibretroLog::log(RETRO_LOG_ERROR) << "[ChaiLove] [filesystem] Error unmounting: " << getLastError() << std::endl;
		return false;
	}
	return true;
}

bool filesystem::mount(const char *archive, const std::string& mountpoint) {
	if (strlen(archive) == 0) {
		return false;
	}
	return mount(std::string(archive), mountpoint);
}

std::string filesystem::getExecutablePath() {
	return std::string(PHYSFS_getBaseDir());
}

bool filesystem::mount(const std::string& archive, const std::string& mountpoint) {
	return mount(archive, mountpoint, true);
}

bool filesystem::mount(const void *data, unsigned int size, const std::string& mountpoint) {
	// TODO: Do we need to register del() callback?
	if (PHYSFS_mountMemory(data, (PHYSFS_uint64)size, NULL, "chailove.zip", mountpoint.c_str(), 1) == 0) {
		return false;
	}
	return true;
}

bool filesystem::mount(const std::string& archive, const std::string& mountpoint, bool appendToPath) {
	// Protect against empty archive/mount points.
	int append = appendToPath ? 1 : 0;
	if (archive.length() <= 0) {
	        //LibretroLog::log(RETRO_LOG_INFO) << "[ChaiLove] [filesystem] Mounting failed because archive was empty." << std::endl;
		return false;
	}

	// Display a message.
	//LibretroLog::log(RETRO_LOG_INFO) << "[ChaiLove] [filesystem] Mounting " << archive << " as " << mountpoint << std::endl;

	// Use the simple mount method if we're mounting the root directory.
	if (mountpoint == "/") {
		int returnValue = PHYSFS_mount(archive.c_str(), mountpoint.c_str(), append);
		if (returnValue == 0) {
			//LibretroLog::log(RETRO_LOG_ERROR) << "[ChaiLove] [filesystem] Error mounting /: " << getLastError() << std::endl;
			return false;
		}
		return true;
	}

	// See if we're mounting a file.
	if (isFile(archive)) {
		// Mount using a handle instead, since we're doing another archive.
		PHYSFS_File* file = openFile(archive);
		if (file != NULL) {
			if (PHYSFS_mountHandle(file, archive.c_str(), mountpoint.c_str(), append) == 0) {
				//LibretroLog::log(RETRO_LOG_ERROR) << "[ChaiLove] [filesystem] Error mounting file: " << getLastError() << std::endl;
				return false;
			}
			return true;
		}
		return false;
	}

	// Check if we're mounting a directory.
	int returnVal = PHYSFS_mount(archive.c_str(), mountpoint.c_str(), append);
	if (returnVal == 0) {
		//LibretroLog::log(RETRO_LOG_ERROR) << "[ChaiLove] [filesystem] Error mounting directory: " << getLastError() << std::endl;
		return false;
	}
	return true;
}

/**
 * Lists all items in the given directory.
 */
std::vector<std::string> filesystem::getDirectoryItems(const std::string& dir) {
	// Construct the list of files that will result.
	std::vector<std::string> result;

	// Ask PhysFS for the enumerated files.
	char** rc = PHYSFS_enumerateFiles(dir.c_str());
	if (rc != NULL) {
		char **i;
		for (i = rc; *i != NULL; i++) {
			// Build the file string.
			std::string thefile(*i);
			result.push_back(thefile);
		}
		PHYSFS_freeList(rc);
	} else {
		//LibretroLog::log(RETRO_LOG_ERROR) << "[ChaiLove] [filesystem] Error enumerating files from " << dir << std::endl;
	}

	return result;
}

bool filesystem::isDirectory(const std::string& filename) {
	PHYSFS_Stat stat;
	if (PHYSFS_stat(filename.c_str(), &stat) == 0) {
		return false;
	}
	return stat.filetype == PHYSFS_FILETYPE_DIRECTORY;
}

bool filesystem::isFile(const std::string& filename) {
	PHYSFS_Stat stat;
	if (PHYSFS_stat(filename.c_str(), &stat) == 0) {
		return false;
	}
	return stat.filetype == PHYSFS_FILETYPE_REGULAR;
}

bool filesystem::isSymlink(const std::string& filename) {
	PHYSFS_Stat stat;
	if (PHYSFS_stat(filename.c_str(), &stat) == 0) {
		return false;
	}
	return stat.filetype == PHYSFS_FILETYPE_SYMLINK;
}

std::vector<std::string> filesystem::lines(const std::string& filename) {
	return lines(filename, "\n");
}

std::vector<std::string> filesystem::lines(const std::string& filename, const std::string& delimiter) {
	std::string str = read(filename);
	std::vector<std::string> strings;

	if (!str.empty()) {
		std::string::size_type pos = 0;
		std::string::size_type prev = 0;
		while ((pos = str.find(delimiter, prev)) != std::string::npos) {
			strings.push_back(str.substr(prev, pos - prev));
			prev = pos + 1;
		}

		// To get the last substring (or only, if delimiter is not found)
		strings.push_back(str.substr(prev));
	}

	return strings;
}

FileInfo filesystem::getInfo(const std::string& path) {
	FileInfo fileInfo;
	PHYSFS_Stat stat;
	if (PHYSFS_stat(path.c_str(), &stat) == 0) {
		return fileInfo;
	}
	switch(stat.filetype) {
		case PHYSFS_FILETYPE_REGULAR:
			fileInfo.type = "file";
			break;
		case PHYSFS_FILETYPE_DIRECTORY:
			fileInfo.type = "directory";
			break;
		case PHYSFS_FILETYPE_SYMLINK:
			fileInfo.type = "symlink";
			break;
		default:
			fileInfo.type = "other";
			break;
	}

	fileInfo.modtime = stat.modtime;
	fileInfo.size = stat.filesize;
	return fileInfo;
}

FileData filesystem::newFileData(const std::string& filepath) {
	FileData f(filepath);
	return f;
}

FileData filesystem::newFileData(const std::string& contents, const std::string& name) {
	FileData f(contents, name);
	return f;
}

std::string filesystem::getSaveDirectory() {
	return "/libretro/saves";
}

bool filesystem::createDirectory(const std::string& name) {
	int ret = PHYSFS_mkdir(name.c_str());
	if (ret == 0) {
		//LibretroLog::log(RETRO_LOG_ERROR) << "[ChaiLove] [filesystem] Failed to create directory: " << getLastError() << std::endl;
		return false;
	}
	return true;
}

bool filesystem::write(const std::string& name, const std::string& data) {
	PHYSFS_File* file = PHYSFS_openWrite(name.c_str());
	if (file == NULL) {
		//LibretroLog::log(RETRO_LOG_ERROR) << "[ChaiLove] [filesystem] Error opening file for writing: " << getLastError() << std::endl;
		return false;
	}
	const char* buffer = data.c_str();
	int bytesWritten = PHYSFS_writeBytes(file, (const void*)buffer, data.size());
	return bytesWritten >= 0;
}

std::string filesystem::getLastError() {
	const char* charErr = PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode());
	if (charErr) {
		return std::string(charErr);
	}
	return "";
}

}  // namespace love
