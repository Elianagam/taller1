#include <iostream>
#include <algorithm>
#include <arpa/inet.h>
#include <vector>
#include <mutex>
#include <queue>
#include <string>
#include <fstream>
#include <cstring>
#include "Block.h"
#include "Safe_Queue.h"
#include "Writer.h"


Writer::Writer(std::vector<Safe_Queue*> &queues, char* name_file,
	int num_threads) :
	safe_queues(queues), name_file(name_file), num_threads(num_threads) {
	outfile.open(name_file, std::ios::out | std::ios::binary);		
	if (strcmp(name_file, "-") == 0) {
		output = &std::cout;
	} else {
		output = &outfile;
	}
}

void Writer::run() {
	uint32_t finish = 0;
	while (finish != safe_queues.size()) {
		finish = 0;
		for (uint32_t i = 0; i < safe_queues.size(); i++) {	
			if (safe_queues[i]->is_close() && safe_queues[i]->is_empty()) {
				// para saltar colas cerradas
				finish++;
			} else if (!safe_queues[i]->is_close() || !safe_queues[i]->is_empty()) { 
				// para escribir:
				std::vector<char> string;
				if (!safe_queues[i]->pop(string)) return;
				output->write(string.data(), string.size());
			} else { 
				// para salir si es que tengo todo cerrado
				return;
			}
		}
	}
}

Writer::~Writer() {
	outfile.close();
}
