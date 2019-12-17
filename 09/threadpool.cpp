#include "threadpool.h"

ThreadPool::ThreadPool(size_t poolSize) 
	: size(poolSize)
	, keep_working(true) 
{
	threads.reserve(size);
	for (size_t i = 0; i < size; i++) {
		threads.push_back(std::thread([this]() {
			while (keep_working) {
				std::unique_lock<std::mutex> lock(mutex);
				if (tasks.empty()) {
					condition.wait(lock);
					continue;
				}
				auto task = tasks.front();
				tasks.pop();
				lock.unlock();
				task();
			}
		}));
	}
}

ThreadPool::~ThreadPool() {
	keep_working = false;

	condition.notify_all();
	for (size_t i = 0; i < threads.size(); i++) {
		threads[i].join();
	}
}
