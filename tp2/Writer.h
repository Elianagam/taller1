#ifndef WRITER_H
#define WRITER_H

#include <iostream>
#include <mutex>
#include <queue>
#include <fstream>
#include <algorithm>
#include <vector>
#include "Block.h"
#include "Safe_Queue.h"
#include "Thread.h"

class Writer : public Thread {
private:
	std::vector<Safe_Queue*> &safe_queues;
	std::ostream *output;
	std::ofstream outfile;
	char* name_file;
	uint32_t num_threads;

public:
	Writer(std::vector<Safe_Queue*> &queues, char* name_file,
		int num_threads);
	
	void run() override; 

	~Writer();
};

#endif
