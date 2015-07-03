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
 #include <memory>

 namespace cxxlib
 {
 	class ThreadPool
 	{
 	public:
 		typedef std::function<void()> Task;
 	public:
 		explicit ThreadPool(const std::string& _name = 
 			std::string("Thread Pool"));
 		~ThreadPool();

 		void setMaxPoolSize(int _max_size)
 		{
 			max_size = _max_size;
 		}

 		std::string name() const
 		{
 			return name;
 		}

 		void setThreadInitCallback(const Task& _callback)
 		{
 			init_callback = _callback;
 		}

 		void start(int num_threads);
 		void stop();
 		size_t size() const;

 		void addTask(const Task& _task);

 	private:
 		// FOR NONCOPYABLE
 		ThreadPool(const ThreadPool& );
 		ThreadPool& operator = (const ThreadPool& );

 	private:
 		inline bool isFull() const
 		{
 			return max_size > 0 && tasks.size() >= max_size;
 		}
 		
 		Task get();

 		void runInternal();

 		mutable std::mutex mutex;
 		std::condition_variable not_empty;
 		std::condition_variable not_full;

 		std::string name;
 		Task init_callback;
 		std::vector<std::shared_ptr<std::thread> > threads;
 		std::queue<Task> tasks;

 		size_t max_size;
 		bool running;
 	};
 }

#endif  // __CXXLIB_THREAD_POOL_H__