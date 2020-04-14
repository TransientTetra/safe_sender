#include "../../include/model/file_metadata.hpp"

FileMetadata::FileMetadata()
{
	extension = "";
	dataSize = 0;
}

FileMetadata::FileMetadata(std::string filename, std::string extension, unsigned long dataSize)
{
	this->filename = filename;
	this->extension = extension;
	this->dataSize = dataSize;
}

const unsigned long &FileMetadata::getDataSize() const
{
	return dataSize;
}

const std::string &FileMetadata::getExtension() const
{
	return extension;
}

const std::string &FileMetadata::getFilename() const
{
	return filename;
}

