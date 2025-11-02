#pragma once
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>


class JobSystem
{
public:
	explicit JobSystem(size_t threadCount = std::thread::hardware_concurrency())
	{
		workers_.reserve(threadCount);
		for (size_t i = 0; i < threadCount; ++i)
		{
			workers_.emplace_back([this]()
			{
				WorkerLoop();
			});
		}
	}

	~JobSystem()
	{
		{
			std::unique_lock<std::mutex> lock(mutex_);
			stop_ = true;
		}
		condition_.notify_all(); // 모든 워커 스레드를 깨움. stop_가 true고, jobQueue_가 비어있으면 종료됨.
		for (std::thread& worker : workers_)
		{
			worker.join();
		}
	}

	void Prepare(size_t jobCount)
	{
		activeJobs_.store(static_cast<int>(jobCount), std::memory_order_relaxed);
	}

	void Enqueue(const std::function<void()>& job)
	{
		{
			std::unique_lock<std::mutex> lock(mutex_);
			jobQueue_.push(job);
		}
		condition_.notify_one();
	}

	void WaitAll()
	{
		while (true)
		{
			const int expected = activeJobs_.load(std::memory_order_relaxed);
			if (expected == 0)
			{
				return;
			}
			activeJobs_.wait(expected, std::memory_order_relaxed); // load후 바뀔 때까지 대기
		}
	}

private:
	void WorkerLoop()
	{
		while (true)
		{
			std::function<void()> job;
			{
				std::unique_lock<std::mutex> lock(mutex_);
				// 락을 놓고 Job이 들어올 때까지 대기
				condition_.wait(lock, [this]() { return stop_ || !jobQueue_.empty(); });
				if (stop_ && jobQueue_.empty())
				{
					return;
				}

				// job을 저장 후 큐에서 제거
				job = jobQueue_.front();
				jobQueue_.pop();
			}

			// 락을 풀고 job 실행
			job();
			if (activeJobs_.fetch_sub(1, std::memory_order_relaxed) - 1 == 0)
			{
				activeJobs_.notify_one(); // 단일 스레드만 WaitAll을 대기한다고 가정
			}
		}
	}

private:
	std::vector<std::thread> workers_;
	std::queue<std::function<void()> > jobQueue_;
	std::mutex mutex_;
	std::condition_variable condition_;
	bool stop_ = false;
	std::atomic_int activeJobs_ = 0;
};