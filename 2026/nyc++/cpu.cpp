// @file: cpu.cpp
// g++ -std=c++23 cpu.cpp -o prog && ./prog
// - Example for x86 machines
// - Tested on g++
#ifndef __GNUC___ 
  #include <cpuid.h>
#else
  static_assert(false,"Unsupported platform, use linux and g++");
#endif

#include <print>


int main(){


// Some other ways to query using compiler intrinsics
  std::println("sse = {}",__builtin_cpu_supports("sse"));
  std::println("sse2 = {}",__builtin_cpu_supports("sse2"));
  std::println("avx = {}",__builtin_cpu_supports("avx"));

}
