#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <queue>
#include <vector>


template<typename T, typename N=int>
class PriorityQueue {
    private:
        typedef std::pair<N, T> PQElement;
        std::priority_queue<PQElement, std::vector<PQElement>,
                            std::greater<PQElement>> pElements;

    public:
        /*
         * @return: true if the queue is empty.
         */
        bool empty();

        /*
         * Get and pop the top element in the queue.
         *
         * @return: The top element in the queue.
         */
        T get();

        /*
         * @param tItem:     The item to put in the queue.
         * @param nPriority: The item's priority.
         */
        void put(T tItem, N nPriority);
};

#include "priority_queue.cpp"

#endif
