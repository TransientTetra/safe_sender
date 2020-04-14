#include "../../include/model/file.hpp"
#include <fstream>
#include <filesystem>

File::File(std::string path)
{
	std::ifstream file_in;
	file_in.open(path);
	unsigned long size = std::filesystem::file_size(std::filesystem::path(path));
	data = RawBytes(size);
	file_in.read(reinterpret_cast<char*>(data.getVectorPtr()), size);

	//todo filename contains extension, remove
	metadata = FileMetadata(std::filesystem::path(path).filename(), std::filesystem::path(path).extension(), size);
}

void File::save(std::string path)
{
	std::ofstream file_out;
	file_out.open(path);
	file_out.write(reinterpret_cast<const char*>(data.getVectorPtr()), getDataSize());
}

const std::string &File::getFilename() const
{
	return metadata.getFilename();
}

const std::string &File::getExtension() const
{
	return metadata.getExtension();
}

const unsigned long &File::getDataSize() const
{
	return metadata.getDataSize();
}

void File::encrypt(Encryption &encryption)
{

}
