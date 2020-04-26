#include "../../include/model/file.hpp"
#include <fstream>
#include <filesystem>

File::File(const std::string& filepath)
: Encryptable(filepath) //this is an ugly hack because encryptable needs to be initialized
{
	std::ifstream fileIn;
	fileIn.open(filepath);
	unsigned long size = std::filesystem::file_size(std::filesystem::path(filepath));
	data = RawBytes(size);
	fileIn.read(reinterpret_cast<char *>(data.BytePtr()), size);

	metadata = FileMetadata(std::filesystem::path(filepath).stem(), std::filesystem::path(filepath).extension(), size);
}

File::File(RawBytes bytes)
: Encryptable(bytes)
{

}

void File::save(const std::string& path)
{
	std::ofstream fileOut;
	fileOut.open(path + metadata.getFilename() + metadata.getExtension());
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
