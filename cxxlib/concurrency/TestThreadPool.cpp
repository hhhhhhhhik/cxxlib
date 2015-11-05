#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <iostream>

#include "ThreadPool.h"
#include "CountDownLatch.h"

void print()
{
	printf("hello world\n");
}

void printString(const std::string& str)
{
	printf("%s\n", str.c_str());
	sleep(2);
}

int main(int argc, char* argv[])
{
	cxxlib::ThreadPool pool("test_thread_pool");
	pool.setMaxPoolSize(10);
	pool.start(5);

	pool.addTask(print);

	for (int i = 0; i < 20; i++)
	{
		char buffer[32];
		snprintf(buffer, sizeof(buffer), "this is task %d", i);
		
		pool.addTask(std::bind(printString, std::string(buffer)));
	}

	cxxlib::CountDownLatch latch(1);
	pool.addTask(std::bind(&cxxlib::CountDownLatch::countDown, &latch));
	latch.wait();

	pool.stop();
	
	return 0;
}
