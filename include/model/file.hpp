#ifndef SAFE_SENDER_FILE_HPP
#define SAFE_SENDER_FILE_HPP


#include "file_metadata.hpp"
#include "raw_bytes.hpp"
#include "encryption/encryptable.hpp"
#include "communication/sendable.hpp"

class File : public Encryptable, public Sendable
{
private:
	FileMetadata metadata;
protected:
public:
	File(const std::string& filepath);
	File(RawBytes bytes);

	void save(const std::string& path);

	const std::string &getFilename() const;
	const std::string &getExtension() const;
};


#endif //SAFE_SENDER_FILE_HPP
