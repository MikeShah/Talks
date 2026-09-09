#include <iostream>
#include <stdlib.h>
#include <sys/resource.h>

#include <x86intrin.h> // __rdtsc

int global;
void foo(){}

auto main(int argc, char* argv[], char* env[]) -> int{
    unsigned long start = __rdtsc();

    int x,y;
    std::cout << "stack 1          : " << &x << std::endl;
    std::cout << "stack 2          : " << &y << std::endl;
    std::cout << "functions        : " << (void*)&(foo) << std::endl;
    std::cout << "globals          : " << &global << std::endl;

    int* heap1 = new int;
    int* heap2 = new int;
    std::cout << "heap 1           : " << heap1 << std::endl;
    std::cout << "heap 2           : " << heap2 << std::endl;

    std::cout << "args             : " << &argv[0] << std::endl;

    std::cout << "env              : " << (void*)getenv("HOME") << std::endl;

    int who = RUSAGE_SELF;
    struct rusage usage;
    getrusage(who,&usage);

    std::cout << "minor page faults: " << usage.ru_minflt << std::endl;
    std::cout << "major page faults: " << usage.ru_majflt << std::endl;
    std::cout << "filesystem input : " << usage.ru_inblock << std::endl;
    std::cout << "filesystem output: " << usage.ru_oublock << std::endl;
    std::cout << "context switches(voluntary) : " << usage.ru_nvcsw<< std::endl;
    std::cout << "context switches(high priority) : " << usage.ru_nivcsw << std::endl;


    std::cout << "elapsed time: " << start - __rdtsc() << std::endl;
    return 0;
}
