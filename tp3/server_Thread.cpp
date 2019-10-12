#include <algorithm>
#include <map>
#include <fstream>
#include <thread>
#include "server_Thread.h"

Thread::Thread() {}

void Thread::start() {
    thread = std::thread(&Thread::run, this);
}

void Thread::join() {
    thread.join();
}

bool Thread::is_dead() { 
	return false;
}

void Thread::stop() {}

void Thread::run() {}

Thread::~Thread() {}

Thread::Thread(Thread&& other) {
    this->thread = std::move(other.thread);
}

// operador por movimiento
Thread& Thread::operator=(Thread&& other) {
    this->thread = std::move(other.thread);
    return *this;
}
