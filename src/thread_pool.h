#pragma once
#include <vector>
#include <thread>
#include <functional>
#include <queue>
#include <mutex>
#include <iostream>

using namespace std;

struct TaskQueue {
	queue<function<void()>> _tasks;
	mutex _mutex;
	atomic<uint32_t> _remaining_tasks = 0;

	template<typename TCallback>
	void addTask(TCallback&& callback);
	void getTask(function<void()>& target_callback);
	static void wait();
	void waitForCompletion() const;
	void workDone();
};

struct Worker {
	int id = 0;
	thread _thread;
	function<void()> _task = nullptr;
	bool _running = true;
	TaskQueue* _queue = nullptr;

	Worker() = default;
	Worker(TaskQueue& _queue, int _id) : id(_id), _queue(&_queue) {
		_thread = thread([this]() {
			run();
		});
	};

	void run();
	void stop();
};

struct ThreadPool
{

	TaskQueue _queue;
	vector<Worker> _workers;
	int _thread_count = 0;

	template<typename TCallback>
	void addTask(TCallback&& callback);
	virtual ~ThreadPool();
	explicit ThreadPool(int thread_count);
	template<typename TCallback>
	void dispatch(uint32_t element_count, TCallback&& callback);
	void waitForCompletion() const;
};

template<typename TCallback>
void TaskQueue::addTask(TCallback&& callback)
{
	lock_guard<mutex> lock_guard(_mutex);
	_tasks.push(forward<TCallback>(callback));
	_remaining_tasks++;
}

template<typename TCallback>
void ThreadPool::addTask(TCallback&& callback)
{
	_queue.addTask(forward<TCallback>(callback));
}

template<typename TCallback>
void ThreadPool::dispatch(uint32_t element_count, TCallback&& callback)
{
	int batch_size = element_count / _thread_count;
	for (int i(0); i < _thread_count; i++) {
		const int start = batch_size * i;
		const int end = start + batch_size;
		addTask([start, end, &callback]() { callback(start, end)});
	}

	if (batch_size * _thread_count < element_count) {
		const uint32_t start = batch_size * _thread_count;
		callback(start, element_count);
	}

	waitForCompletion();
}