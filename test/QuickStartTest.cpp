#define BOOST_TEST_MODULE QuickStartTest

#include "QuickStart.h"

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(QuickStartSuite)

BOOST_AUTO_TEST_CASE(AdditionTest1)
{
    QuickStart quickStart;

    BOOST_CHECK_EQUAL(quickStart.add(1, 1), 2);
    BOOST_CHECK_EQUAL(quickStart.add(-100, -200), -300);

}

BOOST_AUTO_TEST_CASE(AdditionTest2)
{
    QuickStart quickStart;

    BOOST_CHECK_NE(quickStart.add(2, 2), -999);
    BOOST_CHECK_GT(quickStart.add(2, 2), 3);
    BOOST_CHECK_LT(quickStart.add(2, 2), 999);

}

BOOST_AUTO_TEST_CASE(AskForExitTest)
{    
    char c;
    do
    {
        std::cout << "Exit? [Y/N]";
        std::cin >> c;
    } while (c != 'y' && c != 'Y');

}

BOOST_AUTO_TEST_SUITE_END()
