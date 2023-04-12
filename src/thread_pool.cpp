#include "thread_pool.h"

void Worker::run()
{
	while (_running) {
		_queue->getTask(_task);
		if (_task == nullptr) {
			TaskQueue::wait();
		}
		else {
			_task();
			_queue->workDone();
			_task = nullptr;
		}
	}
}

void Worker::stop()
{
	_running = false;
	_thread.join();
}

void TaskQueue::getTask(function<void()>& target_callback)
{
	lock_guard<mutex> lock_gard(_mutex);
	if (_tasks.empty()) return;
	target_callback = move(_tasks.front());
	_tasks.pop();
}

void TaskQueue::wait()
{
	this_thread::yield();
}

void TaskQueue::waitForCompletion() const
{
	while (_remaining_tasks > 0) wait();
}

void TaskQueue::workDone()
{
	lock_guard<mutex> look_guard(_mutex);
	_remaining_tasks--;
}

ThreadPool::~ThreadPool()
{
	for (auto& worker : _workers) {
		worker.stop();
	}
}

ThreadPool::ThreadPool(int thread_count)
{
	_thread_count = thread_count;
	_workers.reserve(thread_count);
	for (int i(0); i < thread_count; i++) {
		_workers.emplace_back(_queue, i);
	}
}

void ThreadPool::waitForCompletion() const
{
	_queue.waitForCompletion();
}
