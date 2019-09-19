#include "Lab.h"

void Lab::call_from_thread(int tid)
{
    using namespace std::literals::chrono_literals;
    std::cout << "Launched by call " << tid << " thread " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(1s);
}

int Lab::run()
{
    std::cout << "Hello, world!" << std::endl;

    // *************************************************************************************
    // overal c++ stuff
    // *************************************************************************************
    {
        OpenFile Temporal0(std::string("Temporal0.txt"));
        Temporal0.ReadLines();
    }
    {
        OpenFile Temporal1("Temporal1.txt");
        Temporal1.ReadLines();
    }

    // *************************************************************************************
    // lambdas
    // *************************************************************************************
    // https://solarianprogrammer.com/2014/08/28/cpp-14-lambda-tutorial/

    auto myLambda = [](int input) { return input * input; };

    // first use
    std::cout << "Lambda with 10 " << myLambda(10) << std::endl;

    // second use
    std::cout << "Lambda with 23 " << myLambda(23) << std::endl;

    // *************************************************************************************
    // templated lambdas
    // *************************************************************************************

    auto func2 = [](auto input) { return input * input; };

    // second use
    std::cout << "Lambda2 with 23 " << func2(23) << std::endl;

    // square of a complex number
    auto c = std::complex<double>(3, -2);
    std::cout << "Lambda2 with " << c << " complex " << func2(c) << std::endl;

    // *************************************************************************************
    // threads  (procs & lambdas)
    // *************************************************************************************
    // https://solarianprogrammer.com/2011/12/16/cpp-11-thread-tutorial/

    auto lambda_from_thread = [](int tid) {
        using namespace std::literals::chrono_literals;
        std::cout << "Launched by lambda " << tid << " thread " << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(1s);
    };

    static const int num_threads = 10;
    std::thread t[num_threads];
    std::thread l[num_threads];
    std::cout << "Launching threads from main" << std::endl;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < num_threads; ++i)
    {
        t[i] = std::thread(Lab::call_from_thread, i);
        l[i] = std::thread(lambda_from_thread, i);
    }

    std::this_thread::sleep_for(1s);

    for (int i = 0; i < num_threads; ++i)
    {
        t[i].join();
        l[i].join();
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cout << "Waited " << elapsed.count() << " ms" << std::endl;

    // *************************************************************************************
    // shared and weak pointers
    // *************************************************************************************
    // https://www.youtube.com/watch?v=EWoMjuN5OH4&t=94s
    Dog::RunTests();

    char c0;
    do
    {
        std::cout << "Exit [Y/N]?";
        std::cin >> c0;
    } while (c0 != 'Y' && c0 != 'y');

    return 0;
}
