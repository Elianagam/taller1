#include <algorithm>
#include <map>
#include <fstream>
#include <thread>
#include "Safe_Queue.h"
#include "Thread.h"

Thread::Thread() {}

void Thread::start() {
    thread = std::thread(&Thread::run, this);
}

void Thread::join() {
    thread.join();
}

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

