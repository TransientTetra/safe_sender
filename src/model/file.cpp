#include "../../include/model/file.hpp"
#include <fstream>
#include <filesystem>

File::File(std::string path)
{
	std::ifstream file_in;
	file_in.open(path);
	unsigned long size = 0;
	while (file_in)
	{
		++size;
		char c;
		file_in.get(c);
		data.push(reinterpret_cast<std::byte &>(c));
	}
	//a workaround because ifstream keeps adding \n at the end of file for some reason
	--size;
	data.pop();

	metadata = FileMetadata(std::filesystem::path(path).filename(), std::filesystem::path(path).extension(), size);
}

void File::save(std::string path)
{
	std::ofstream file_out;
	file_out.open(path);
//	for (unsigned long i = 0; i < getDataSize(); ++i)
//	{
//		file_out.put(reinterpret_cast<const char &>(data.getByte(i)));
//	}
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
