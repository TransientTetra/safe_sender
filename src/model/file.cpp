#include "../../include/model/file.hpp"
#include <fstream>
#include <filesystem>

File::File(const std::string& path)
: Encryptable(path)
{
	std::ifstream fileIn;
	fileIn.open(path);
	unsigned long size = std::filesystem::file_size(std::filesystem::path(path));
	data = RawBytes(size);
	fileIn.read(reinterpret_cast<char *>(data.BytePtr()), size);

	metadata = FileMetadata(std::filesystem::path(path).stem(), std::filesystem::path(path).extension(), size);
}

File::File(RawBytes bytes)
: Encryptable(bytes)
{

}

void File::save(const std::string& path)
{
	std::ofstream fileOut;
	fileOut.open(path);
	fileOut.write(reinterpret_cast<const char*>(data.BytePtr()), getDataSize());
}

const std::string &File::getFilename() const
{
	return metadata.getFilename();
}

const std::string &File::getExtension() const
{
	return metadata.getExtension();
}