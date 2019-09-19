#include <iostream>
#include <thread>
#include "QuickStart.h"
#include "Dog.h"
#include "MulticastSender.h"
#include "MulticastReceiver.h"
#include "Dog.h"

int main(int argc, char *argv[])
{
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