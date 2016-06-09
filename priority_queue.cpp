#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE

#include "priority_queue.hpp"


template<typename T, typename N>
bool PriorityQueue<T, N>::Empty() const
{
    return pElements.empty();
}

template<typename T, typename N>
T PriorityQueue<T, N>::Get()
{
    T BestItem = pElements.top().second;
    pElements.pop();
    return BestItem;
}

template<typename T, typename N>
void PriorityQueue<T, N>::Put( const T Item, const N nPriority )
{
    pElements.emplace( nPriority, Item );
}

#endif // PRIORITY_QUEUE
