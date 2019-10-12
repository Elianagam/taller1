#include <iostream>
#include <string>
#include <thread>
#include <queue>
#include <algorithm>
#include <condition_variable>
#include "Block.h"
#include "Safe_Queue.h"
#include <cmath>
#include <cerrno>
#include <cstdio>
#include <vector>


Safe_Queue::Safe_Queue(uint32_t max_queue) :
	max_size(max_queue), _shutdown(false) {}

void Safe_Queue::push(Block &block) {
	std::unique_lock<std::mutex> lock(mutex);
	while (queue.size() == max_size) {
		cv_push.wait(lock);
	}
	queue.push(std::move(block));
	cv_pop.notify_all();
}

bool Safe_Queue::pop(std::vector<char> &block_compress) {
	std::unique_lock<std::mutex> lock(mutex);

	while(!_shutdown && queue.empty()) {
		cv_pop.wait(lock);
	}
	if (_shutdown && queue.empty()) {
		return false;
	} else {
		Block block = std::move(queue.front());
		block_compress = std::move(block.get_compress());
		queue.pop();
		cv_push.notify_all();
		return true;
	}
}

bool Safe_Queue::is_empty() {
	std::unique_lock<std::mutex> lock(mutex);
	return queue.empty();
}

void Safe_Queue::close() {
	_shutdown = true;
	cv_pop.notify_all();
}

bool Safe_Queue::is_close() {
	std::unique_lock<std::mutex> lock(mutex);
	return _shutdown;
}

Safe_Queue::Safe_Queue(Safe_Queue&& other) {
	std::unique_lock<std::mutex> lock(mutex);
    this->queue = std::move(other.queue);
    this->max_size = other.max_size;
}

Safe_Queue& Safe_Queue::operator=(Safe_Queue&& other) {
	std::unique_lock<std::mutex> lock(mutex);
    this->queue = std::move(other.queue);
    this->max_size = other.max_size; 
    return *this;
}

