#ifndef SAFE_SENDER_FILE_METADATA_HPP
#define SAFE_SENDER_FILE_METADATA_HPP


#include <string>

class FileMetadata
{
private:
	std::string filename;
	std::string extension;
	unsigned long dataSize;
public:
	FileMetadata();
	FileMetadata(std::string filename, std::string extension, unsigned long dataSize);

	const unsigned long &getDataSize() const;
	const std::string &getExtension() const;
	const std::string &getFilename() const;
};


#endif //SAFE_SENDER_FILE_METADATA_HPP
