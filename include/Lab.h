#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <complex>
#include "OpenFile.h"
#include "Dog.h"

class Lab
{

public:

    static void call_from_thread(int tid);
    static int run();

};