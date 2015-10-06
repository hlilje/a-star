#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE

#include "priority_queue.hpp"


template<typename T, typename N>
bool PriorityQueue<T, N>::empty() {
    return pElements.empty();
}

template<typename T, typename N>
T PriorityQueue<T, N>::get() {
    T best_item = pElements.top().second;
    pElements.pop();
    return best_item;
}

template<typename T, typename N>
void PriorityQueue<T, N>::put(T tItem, N nPriority) {
    pElements.emplace(nPriority, tItem);
}

#endif
