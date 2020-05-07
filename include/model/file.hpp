#ifndef SAFE_SENDER_FILE_HPP
#define SAFE_SENDER_FILE_HPP


#include "raw_bytes.hpp"
#include "encryption/encryptable.hpp"
#include "communication/sendable.hpp"

struct FileMetadata
{
	std::string filename;
	std::string extension;
	unsigned long dataSize;
};

class File : public Encryptable, public Sendable
{
private:
	FileMetadata metadata;
protected:
public:
	File(const std::string& filePath);
	File(RawBytes bytes);

	void save(const std::string& path);

	const FileMetadata &getMetadata() const;

	void setMetadata(const FileMetadata &metadata);
};


#endif //SAFE_SENDER_FILE_HPP
