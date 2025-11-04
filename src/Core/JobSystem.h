#pragma once

#include <format>
#include <functional>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>

class JobSystem
{
public:
	explicit JobSystem(size_t threadCount = std::thread::hardware_concurrency());
	~JobSystem();
	void Prepare(size_t jobCount);
	void Enqueue(std::function<void()> fun);
	void WaitAll();

private:
	void WorkerLoop(int index);

private:
	std::vector<std::thread> workers_;
	std::queue<std::function<void()>> jobQueue_;
	std::mutex mutex_;
	std::condition_variable condition_;
	bool stop_ = false;
	std::atomic_int activeJobs_ = 0;
};