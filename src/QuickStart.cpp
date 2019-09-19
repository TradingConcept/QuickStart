#include "QuickStart.h"

int QuickStart::add(int a, int b)
{
    return (a + b);
}

void QuickStart::Run() {

    auto q = new QuickStart();
    if (q->add(1, 2) != 3)
    {
        std::cout << "QuickStartLib Error" << std::endl;
    }
    else
    {
        std::cout << "QuickStartLib Success" << std::endl;
    }

    delete q;

}