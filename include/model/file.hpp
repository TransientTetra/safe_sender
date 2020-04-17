#ifndef SAFE_SENDER_FILE_HPP
#define SAFE_SENDER_FILE_HPP


#include "file_metadata.hpp"
#include "raw_bytes.hpp"
#include "encryptable.hpp"
#include "sendable.hpp"

class File : public Encryptable, public Sendable
{
private:
	FileMetadata metadata;
protected:
public:
	File(const std::string& path);
	File(RawBytes bytes);

	void save(const std::string& path);

	const std::string &getFilename() const;
	const std::string &getExtension() const;
};


#endif //SAFE_SENDER_FILE_HPP
