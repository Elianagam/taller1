#include <iostream>
#include <fstream>
#include <algorithm>
#include <arpa/inet.h>
#include <mutex>
#include "Block.h"
#include "Safe_Queue.h"
#include "Thread.h"
#include "Compressor.h"
#include "File_Reader.h"
#include <cmath>
#include <cerrno>
#include <cstdio>

#define BYTE4 4

Compressor::Compressor(Safe_Queue* queue, File_Reader &file_reader, 
	uint32_t len_block, uint32_t position, uint32_t cant_threads) :
	safe_queue(queue),
	file_reader(file_reader),
	len_block(len_block),
	position(position),
	cant_threads(cant_threads) {}

void Compressor::run() {
	while(1) {
		Block block(len_block);
		if (!file_reader.read(block, position)) {
			break;
		}
		position += cant_threads;
		block.compress();
		safe_queue->push(block);
	}
	safe_queue->close();
}

Compressor::~Compressor() {}
