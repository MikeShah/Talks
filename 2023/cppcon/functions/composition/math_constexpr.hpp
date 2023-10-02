// math_constexpr.hpp
#pragma once

// Wrap all functions in 'namespace'
namespace mike{
		constexpr int add(const int a, const int b){	return a+b; }
		constexpr int sub(const int a, const int b){ 	return a-b; }
		constexpr int mul(const int a, const int b){ 	return a*b; }
}
