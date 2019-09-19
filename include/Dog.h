#pragma once
#include<memory>
#include <iostream>
#include <string>

using namespace std ;

class Dog {
    int age ;
    string name ;
public:
    Dog(int age, string name);
    Dog(string);
    ~Dog();
    void bark();
    static void Run();
    static void RunTests();
    static void RunAll();
};