#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include <iostream>
#include <fstream>
#include <algorithm>
#include <arpa/inet.h>
#include "Safe_Queue.h"
#include "File_Reader.h"
#include "Thread.h"

class Compressor : public Thread {
private:
	Safe_Queue* safe_queue;
	File_Reader &file_reader;
	uint32_t len_block;
	uint32_t position;
	uint32_t cant_threads;

	void close_queue();
public:
	Compressor(Safe_Queue* queue, File_Reader &file_reader, 
		uint32_t len_block, uint32_t position, uint32_t cant_threads);

	void run() override;

	~Compressor();
};

#endif
