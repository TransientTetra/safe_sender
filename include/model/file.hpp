#ifndef SAFE_SENDER_FILE_HPP
#define SAFE_SENDER_FILE_HPP


#include "file_metadata.hpp"
#include "raw_bytes.hpp"
#include "encryptable.hpp"
#include "sendable.hpp"

class File : public Encryptable, Sendable
{
private:
	FileMetadata metadata;
public:
	File(std::string path);

	void save(std::string path);

	const std::string &getFilename() const;
	const std::string &getExtension() const;
	const unsigned long &getDataSize() const;

	void encrypt(Encryption &encryption);
	void decrypt(Encryption &encryption);
};


#endif //SAFE_SENDER_FILE_HPP
