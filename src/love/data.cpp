#include "data.h"
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <string>
#include <stdexcept>
#include <sstream>
#include <vector>
#include "compat/zlib.h"
#include "utils/md5.h"
#include "TinySHA1.hpp"
#include <cppcodec/base64_default_rfc4648.hpp>
#include <cppcodec/hex_default_lower.hpp>

namespace love {

std::string data::compress(const std::string& str) {
	return compress(str, Z_BEST_SPEED);
}

std::string data::compress(const std::string& str, int compressionlevel) {
	if (compressionlevel < 0 || compressionlevel > 9) {
		compressionlevel = Z_BEST_SPEED;
	}
	z_stream zs;
	memset(&zs, 0, sizeof(zs));

	if (deflateInit(&zs, compressionlevel) != Z_OK) {
		//LibretroLog::log(RETRO_LOG_ERROR) << "[ChaiLove] [data] deflateInit failed while compressing." << std::endl;
		return str;
	}

	zs.next_in = (Bytef*)str.data();
	zs.avail_in = str.size();

	int ret;
	char outbuffer[32768];
	std::string outstring;

	do {
		zs.next_out = reinterpret_cast<Bytef*>(outbuffer);
		zs.avail_out = sizeof(outbuffer);

		ret = deflate(&zs, Z_FINISH);

		if (outstring.size() < zs.total_out) {
			outstring.append(outbuffer,
							 zs.total_out - outstring.size());
		}
	} while (ret == Z_OK);

	deflateEnd(&zs);

	if (ret != Z_STREAM_END) {
		//LibretroLog::log(RETRO_LOG_ERROR) << "[ChaiLove] [data] Exception during zlib compression: (" << ret << ") " << zs.msg << std::endl;
		return str;
	}

	return outstring;
}

std::string data::decompress(const std::string& str) {
	z_stream zs;
	memset(&zs, 0, sizeof(zs));

	if (inflateInit(&zs) != Z_OK)
		throw(std::runtime_error("inflateInit failed while decompressing."));

	zs.next_in = (Bytef*)str.data();
	zs.avail_in = str.size();

	int ret;
	char outbuffer[32768];
	std::string outstring;

	do {
		zs.next_out = reinterpret_cast<Bytef*>(outbuffer);
		zs.avail_out = sizeof(outbuffer);

		ret = inflate(&zs, 0);

		if (outstring.size() < zs.total_out) {
			outstring.append(outbuffer,
							 zs.total_out - outstring.size());
		}
	} while (ret == Z_OK);

	inflateEnd(&zs);

	if (ret != Z_STREAM_END) {
		std::ostringstream oss;
		oss << "[ChaiLove] [data] Exception during zlib decompression: (" << ret << ") " << zs.msg;
		throw(std::runtime_error(oss.str()));
	}

	return outstring;
}

std::string data::encode(const std::string& containerType, const std::string& format, const std::string& sourceString) {
	if (format == "base64") {
		std::string encoded = base64::encode(sourceString);
		return encoded;
	}

	if (format == "hex") {
		std::string encoded = hex::encode(sourceString);
		return encoded;
	}

	//LibretroLog::log(RETRO_LOG_ERROR) << "[ChaiLove] Warning: love.data.encode format not found: " << format << "." << std::endl;
	return sourceString;
}

std::string data::decode(const std::string& containerType, const std::string& format, const std::string& sourceString) {
	if (format == "base64") {
		std::vector<unsigned char> decodedVector = base64::decode(sourceString);
		std::string decoded(decodedVector.begin(), decodedVector.end());
		return decoded;
	}

	if (format == "hex") {
		std::vector<unsigned char> decodedVector = hex::decode(sourceString);
		std::string decoded(decodedVector.begin(), decodedVector.end());
		return decoded;
	}

	//LibretroLog::log(RETRO_LOG_ERROR) << "[ChaiLove] Warning: love.data.decode format not found: " << format << "." << std::endl;
	return sourceString;
}

std::string data::hash(const std::string& hashFunction, const std::string& data) {
	if (hashFunction == "md5") {
		return hash_md5(data);
	}

	if (hashFunction == "sha1") {
		return hash_sha1(data);
	}

	//LibretroLog::log(RETRO_LOG_ERROR) << "[ChaiLove] Error: Hash function not found: " << hashFunction << "." << std::endl;
	return "";
}

std::string data::hash_md5(const std::string& data) {
	const char* input = data.c_str();
	unsigned char digest[16];

	// Calculate the MD5 hash using libretro-common.
	MD5_CTX context;
	MD5_Init(&context);
	MD5_Update(&context, input, strlen(input));
	MD5_Final(digest, &context);

	// Construct the MD5 hash string.
	char md5string[33+8];
	for (int i = 0; i < 16; ++i) {
		/*
		  sizeof(&md5string[i * 2]) is a sizeof of a pointer, so 4 or 8
		  instead of intended 3 (2 hex digits + \0) leading
		  to a potential overflow
		*/
		snprintf(&md5string[i * 2], 3, "%02x", (unsigned int)digest[i]); /* NOLINT(runtime/printf).  */
	}

	// Output the hash.
	std::string output(md5string);
	return output;
}

std::string data::hash_sha1(const std::string& data) {
	sha1::SHA1 s;
	s.processBytes(data.c_str(), data.size());
	uint32_t digest[5];
	s.getDigest(digest);
	char tmp[48];
	snprintf(tmp, sizeof(tmp), "%08x%08x%08x%08x%08x",
		 (unsigned int) digest[0], (unsigned int) digest[1],
		 (unsigned int) digest[2], (unsigned int) digest[3],
		 (unsigned int) digest[4]);
	return std::string(tmp);
}

}  // namespace love
