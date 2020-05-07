#include "../../include/model/file.hpp"
#include <fstream>
#include <filesystem>

File::File(const std::string& filePath)
: Encryptable(filePath) //this is an ugly hack because encryptable needs to be initialized
{
	std::ifstream fileIn;
	fileIn.open(filePath);
	unsigned long size = std::filesystem::file_size(std::filesystem::path(filePath));
	data = RawBytes(size);
	fileIn.read(reinterpret_cast<char *>(data.BytePtr()), size);

	metadata.filename = std::filesystem::path(filePath).stem();
	metadata.extension = std::filesystem::path(filePath).extension();
	metadata.dataSize = size;
}

File::File(RawBytes bytes)
: Encryptable(bytes)
{

}

void File::save(const std::string& path)
{
	std::ofstream fileOut;
	fileOut.open(path + metadata.filename + metadata.extension);
	fileOut.write(reinterpret_cast<const char*>(data.BytePtr()), getDataSize());
}

const FileMetadata &File::getMetadata() const
{
	return metadata;
}

void File::setMetadata(const FileMetadata &metadata)
{
	File::metadata = metadata;
}
