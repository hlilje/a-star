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
        bool Empty() const;

        T Get();

        void Put(const T Item, const N nPriority);
};

#include "priority_queue.cpp"

#endif // PRIORITY_QUEUE_H
