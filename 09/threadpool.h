#ifndef threadpool_h
#define threadpool_h

#include <functional>
#include <future>
#include <queue>
#include <thread>
#include <vector>

class ThreadPool {
public:
	using TaskType = std::function<void()>;

	explicit ThreadPool(size_t poolSize);
	ThreadPool(const ThreadPool&) = delete;
	ThreadPool& operator=(const ThreadPool&) = delete;
	ThreadPool(ThreadPool&&) = delete;
	ThreadPool& operator=(ThreadPool&&) = delete;  
	~ThreadPool();

	// pass arguments by value
	template <class Func, class... Args>
	auto exec(Func func, Args... args) -> std::future<decltype(func(args...))> {
		auto task = std::make_shared<std::packaged_task<decltype(func(args...))()>>(
			std::bind(func, args...));
		auto future = task->get_future();

		{
			std::unique_lock<std::mutex> lock(mutex);
			tasks.push([task]() { (*task)(); });
		}

		condition.notify_one();
		return future;
	}
	
private:
	std::vector<std::thread> threads;
	std::queue<TaskType> tasks;
	std::mutex mutex;
	std::condition_variable condition;
	bool keep_working;
	size_t size;
};

#endif
