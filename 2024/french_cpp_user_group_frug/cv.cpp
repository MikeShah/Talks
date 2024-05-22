// @file cv.cpp
// g++ -std=c++23 async.cpp -o prog -lpthread
#include <iostream>
#include <thread>   
#include <vector>
#include <future> // for std::async
#include <chrono>
#include <queue>

auto cv = std::condition_variable{};
auto q = std::queue<int>{};
auto mtx = std::mutex{};
// Protects the shared queue
constexpr int sentinel = -1; // Value to signal that we are done
void print_ints() {
		auto i = 0;
		while (i != sentinel) {
				{
						auto lock = std::unique_lock<std::mutex>{mtx};
						while (q.empty()) {
								cv.wait(lock); // The lock is released while waiting
						}
						i = q.front();
						q.pop();
				}
				if (i != sentinel) {
						std::cout << "Got: " << i << '\n';
				}
		}
}
auto generate_ints() {
		for (auto i : {1, 2, 3, sentinel}) {
				std::this_thread::sleep_for(std::chrono::seconds(1));
				{
								auto lock = std::scoped_lock{mtx};
						q.push(i);
				}
				cv.notify_one();
		}
}
int main() {
		auto producer = std::jthread{generate_ints};
		auto consumer = std::jthread{print_ints};
}
