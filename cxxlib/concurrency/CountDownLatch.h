/*
 * CountDownLatch.h
 *
 *  Created on: 20150703
 *      Author: Huang
 */

 #ifndef __CXXLIB_COUNTDOWNLATCH_H__
 #define __CXXLIB_COUNTDOWNLATCH_H__

 #include <mutex>
 #include <condition_variable>

 namespace cxxlib
 {
 	class CountDownLatch
 	{
 	public:
 		explicit CountDownLatch(int _count)
 				: count(_count),
 				  mutex(),
 				  cond()
 		{
 		}

 		~CountDownLatch()
 		{
 		}

 		void wait()
 		{
 			std::unique_lock<std::mutex> lock(mutex);
 			while (count > 0)
 			{
 				cond.wait();
 			}
 		}

 		void countDown()
 		{
 			std::unique_lock<std::mutex> lock(mutex)
 			--count;
 			if (count == 0)
 			{
 				cond.notify_all();
 			}
 		}

 		int getCount() const
 		{
 			std::unique_lock<std::mutex> lock(mutex)
 			return count;
 		}

 	private:
 		// FOR NONCOPYABLE
 		CountDownLatch(const CountDownLatch& );
 		CountDownLatch& operator = (const  CountDownLatch& );

 	private:
 		mutable std::mutex mutex;
 		std::condition_variable cond;
 		int count;
 	};
 }


 #endif  //  __CXXLIB_COUNTDOWNLATCH_H__