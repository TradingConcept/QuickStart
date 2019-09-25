#include <iostream>
#include <thread>
#include <atomic>
#include <thread>

#include <boost/date_time/posix_time/posix_time.hpp>

#include "QuickStart.h"
#include "Dog.h"
#include "MulticastSender.h"
#include "MulticastReceiver.h"
#include "Dog.h"

#include "ConcurrentCollections.hpp"
#include "ParallelLib.hpp"
#include "LoggingLib.hpp"

const int NUM_THREADS = 8;
Collections::ConcurrentDictionary<std::string, int> *dict3;

void ThreadedInsert(int tid)
{
    std::stringstream s;
    s << "Launched by lambda " << tid << " thread " << std::this_thread::get_id() ;
    Logging::Info(s);

    for (int i = 0; i < 1000 * 1000; i++)
    {
        dict3->TryAdd(std::to_string(i), i);
    }
}

void TestConcurrentCollections()
{
    std::cout << "TestConcurrentCollections..." << std::endl;

    dict3 = new Collections::ConcurrentDictionary<std::string, int>();
    dict3->PrintDictionary();

    auto now1 = boost::posix_time::microsec_clock::local_time();

    std::thread ThreadsDict[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++)
    {
        ThreadsDict[i] = std::thread(ThreadedInsert, i);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        ThreadsDict[i].join();
    }

    auto now2 = boost::posix_time::microsec_clock::local_time();
    auto diff = (now2 - now1).total_milliseconds();

    std::cout << "Size " << dict3->size() << " " << now1 << " - " << diff << " ms" << std::endl;

    delete dict3;
}

void TestParallelLib()
{
    std::cout << "TestParallelLib..." << std::endl;
}

int main(int argc, char *argv[])
{

    TestConcurrentCollections();
    TestParallelLib();

    std::cout << "Press any key to continue..." << std::endl;
    std::getchar();

    std::cout << "Initializng the beast..." << std::endl;

    QuickStart::Run();
    Dog::Run();

    auto treceiver0 = std::thread(MulticastReceiver::Run);
    auto treceiver1 = std::thread(MulticastReceiver::Run);
    auto treceiver2 = std::thread(MulticastReceiver::Run);
    std::this_thread::sleep_for(1s);

    auto tsender = std::thread(MulticastSender::Run);
    std::this_thread::sleep_for(1s);

    tsender.join();

    treceiver0.join();
    treceiver1.join();
    treceiver2.join();

    char c;
    do
    {
        std::cout << "Exit? [Y/N]";
        std::cin >> c;
    } while (c != 'y' && c != 'Y');

    return 0;

    std::cout << "Initializng the beast..." << std::endl;
}