/*
 * ThreadPool.h
 *
 *  Created on: 20150609
 *      Author: Huang
 */

 #ifndef __CXXLIB_THREAD_POOL_H__
 #define __CXXLIB_THREAD_POOL_H__

 #include <queue>
 #include <string>
 #include <vector>

 #include <thread>
 #include <mutex>
 #include <functional>
 #include <condition_variable>

 namespace cxxlib
 {
 	class ThreadPool
 	{
 	public:
 		typedef std::function<void()> Task;
 	public:
 		explicit ThreadPool(const std::string& name = 
 			std::string("Thread Pool"));
 		~ThreadPool();

 		void setMaxPoolSize(int _max_size)
 		{
 			max_size = _max_size;
 		}

 		const std::string name() const
 		{
 			return name;
 		}

 		void setThreadInitCallback(const Task& _callback)
 		{
 			callback = _callback;
 		}

 		void start(int num);
 		void stop();
 		size_t size() const;

 		void run(const Task& _task);

 	private:
 		// FOR NONCOPYABLE
 		ThreadPool(const ThreadPool& );
 		ThreadPool& operator = (const ThreadPool& );

 	private:
 		bool isFull() const;
 		Task get();

 		mutable std::mutex mutex;
 		std::condition_variable cond_not_empty;
 		std::condition_variable cond_not_full;

 		std::string name;
 		Task callback;
 		std::vector<std::thread*> threads;
 		std::queue<Task> queue;

 		size_t max_size;
 		bool running;
 	};
 }

#endif  // __CXXLIB_THREAD_POOL_H__