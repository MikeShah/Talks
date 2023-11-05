// priority_queue.cpp
#include <iostream>
#include <queue> // priority_queue
#include <deque>

int main(){

    std::priority_queue<int> priorityQueue;
    priorityQueue.push(32);
    priorityQueue.push(33);
    priorityQueue.push(31);

    while(!priorityQueue.empty()){
        int t = priorityQueue.top();
        std::cout << "ordering: " << t << std::endl;
        priorityQueue.pop();
    }

    return 0;
}
