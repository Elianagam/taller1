#include <iostream>
#include <algorithm>
#include <arpa/inet.h>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include <stdio.h>
#include "Block.h"
#include "Writer.h"
#include "Thread.h"
#include "File_Reader.h"
#include "Compressor.h"
#include "Safe_Queue.h"

void main_threads(char* name_file_in, char* name_file_out,
	uint32_t len_block, uint32_t num_threads, uint32_t max_queue) {
	std::vector<Thread*> threads;
	std::vector<Safe_Queue*> queues;

	File_Reader infile(name_file_in, len_block);

	for (uint32_t i = 0; i < num_threads; i++) {
		queues.push_back(new Safe_Queue(max_queue));
		threads.push_back(new Compressor(queues[i], infile, 
			(uint32_t)len_block, i, num_threads));
	}
	threads.push_back(new Writer(queues, name_file_out, num_threads));

	for (uint32_t i = 0; i < threads.size(); i++)
		threads[i]->start();

    for (uint32_t i = 0; i < threads.size(); i++) {
        threads[i]->join();
    }

    for (uint32_t i = 0; i < threads.size(); i++) {
        delete threads[i];
        if (i < queues.size()) 
        	delete queues[i];
    }
}

int main(int argc, char* argv[]) {
	if (argc != 6) return 1;

	uint32_t num_threads = (uint32_t)std::stoi(argv[2]);
	uint32_t max_queue = (uint32_t)std::stoi(argv[3]);
	uint32_t len_block = (uint32_t)std::stoi(argv[1]);

	main_threads(argv[4], argv[5], len_block, 
		num_threads, max_queue);
	return 0; 
}
