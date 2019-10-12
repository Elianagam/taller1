#ifndef FILE_READER_H
#define FILE_READER_H

#include "Block.h"

class File_Reader {
private:
	char* name_file;
	uint32_t len_block;
	std::istream *input;
	std::ifstream infile;
	std::mutex mutex;
public:
	File_Reader(char* name_file, uint32_t len_block);

	bool read(Block &block, uint32_t position);

	~File_Reader();
};

#endif
