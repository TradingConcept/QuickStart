// Win32Project1.cpp : Defines the entry point for the console application.
// http://eli.thegreenplace.net/2016/c11-threads-affinity-and-hyperthreading/
//

#include "stdafx.h"

#include <windows.h>
#include <strsafe.h>

#include <thread>
#include <mutex>
#include <vector>

#include <iostream>
#include <math.h>
#include <list>
#include <ctime>

#define NTHREADS 1

DWORD WINAPI threadProc(LPVOID p)
{
	std::cout << "thread " << (DWORD)p << " CPU " << WIN32::GetCurrentProcessorNumber << std::endl;

	std::list<int> primos;

	auto count = (int)pow(2, 25);
	for (int i = 1; i < count; i += 2)
	{
		auto limit = (int)sqrt(i);
		bool residual = false;
		for (int j = 3; j <= limit; j += 2)
		{
			if (i % j == 0)
			{
				residual = true;
				break;
			}
		}
		if (!residual)
		{
			// std::cout << i << std::endl;
			primos.push_back(i);
		}
	}

	return 0;
}

int main()
{
	unsigned num_cpus = std::thread::hardware_concurrency();
	std::cout << "Launching " << num_cpus << " threads\n";
	num_cpus /= 4;

	//std::cout << "C++ Prime number calculator!" << std::endl;

	//clock_t begin = std::clock();

	//for (int i = 0; i < NTHREADS; i++)
	//{
	//	WIN32::CreateThread(NULL, 0, threadProc, (LPVOID)i, 0, NULL);
	//}

	//clock_t end = std::clock();

	//std::cout << "Ended in " << double(end - begin) / CLOCKS_PER_SEC << std::endl;

	// A mutex ensures orderly access to std::cout from multiple threads.
	std::mutex iomutex;
	std::vector<std::thread> threads(num_cpus);
	for (unsigned i = 0; i < num_cpus; ++i) 
	{
		threads[i] = std::thread([&iomutex, i] {
			{
				// Use a lexical scope and lock_guard to safely lock the mutex only for
				// the duration of std::cout usage.
				std::lock_guard<std::mutex> iolock(iomutex);
				std::cout << "Thread #" << i << ": on CPU sched_getcpu() \n";
			}

			// Simulate important work done by the tread by sleeping for a bit...
			// std::this_thread::sleep_for(std::chrono::milliseconds(8000));
			threadProc((LPVOID)i);

		});

		//// Create a cpu_set_t object representing a set of CPUs. Clear it and mark
		//// only CPU i as set.
		//cpu_set_t cpuset;
		//CPU_ZERO(&cpuset);
		//CPU_SET(i, &cpuset);
		//int rc = pthread_setaffinity_np(threads[i].native_handle(),
		//	sizeof(cpu_set_t), &cpuset);
		//if (rc != 0) {
		//	std::cerr << "Error calling pthread_setaffinity_np: " << rc << "\n";
		//}

	}

	for (auto& t : threads) {
		t.join();
	}

	std::cout << "Press enter... ";
	getchar();

	return 0;

}


