#include"extern.h"
#include<iostream>
int static test_entrance(const char* output_path);

#ifndef _uintMax_
#define _uintMax_ 0xffffffffffffffff
#endif
int test_entrance_old(const char* output_path);
#include<cmath>
int main(int argc, char* argv[])
{
    int error;
    try
    {
        error = test_entrance_old("./");
    }
    catch (Pikachu::PikaError& E)
    {
        std::cout << "int main(): " << std::endl;
        E.show(stderr);
    }
    return error;
}


