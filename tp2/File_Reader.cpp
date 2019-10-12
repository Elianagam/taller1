#include <iostream>
#include <cstring>
#include <fstream>
#include <stdio.h>
#include <fstream>
#include <arpa/inet.h>
#include <mutex>
#include "Block.h"
#include "File_Reader.h"

#define BYTE4 4

File_Reader::File_Reader(char* name_file, uint32_t len_block) :
	name_file(name_file), len_block(len_block) {
	infile.open(name_file, std::fstream::in | std::fstream::binary);
	if (strcmp(name_file, "-") == 0) {
		input = &std::cin;
	} else {
		input = &infile;
	}
}

bool File_Reader::read(Block &block, uint32_t position) {
	std::unique_lock<std::mutex> lock(mutex);

	input->clear();
	input->seekg(len_block * position * BYTE4);
	if (input->fail() || input->tellg() == -1 || input->eof()) {
		return false;
	}
	uint32_t hex = 0;
	while (!block.is_full()
			&& input->read((char*)&hex, BYTE4)) {
		block.add(ntohl(hex));
	}
	if (block.get_size() == 0) return false;
	return true;
}

File_Reader::~File_Reader() {
	infile.close();
}
