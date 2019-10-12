#ifndef SAFE_QUEUE_H
#define SAFE_QUEUE_H

#include <mutex>
#include <queue>
#include <algorithm>
#include <condition_variable>
#include <vector>
#include "Block.h"

class Safe_Queue {
private:
	std::queue<Block> queue;
	uint32_t max_size;
	std::mutex mutex;
	std::condition_variable cv_pop;
	std::condition_variable cv_push;
	bool _shutdown;
	
public:
	explicit Safe_Queue(uint32_t max_queue);

	void push(Block &block);

	bool is_full();

	void close();

	bool is_close();

	bool pop(std::vector<char> &block_compress);

	bool is_empty();

	Safe_Queue(const Safe_Queue&) = delete;

	Safe_Queue& operator=(const Safe_Queue&) = delete;

	Safe_Queue(Safe_Queue&& other);

	Safe_Queue& operator=(Safe_Queue&& other);
};

#endif
