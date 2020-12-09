#include "priorityqueue.h"

PriorityQueue::PriorityQueue() {
    //do nothing
}

PriorityQueue::PriorityQueue(Vertex& s) {
    pq.push(std::make_pair(s, 0));
}

/*
 * Since unable to edit, add duplicates to priority queue, but will only deal with one with lowest cost
 */
void PriorityQueue::push(std::pair<Vertex, int> p) {
    pq.push(p);
}

/*
 * needs to only deal with min dist for each vertex
 */
std::pair<Vertex, int> PriorityQueue::pop() { //this function is questionable in terms of functionality
    std::pair<Vertex, int> t = pq.top();
    pq.pop(); //questionable?
    return t;
}

std::pair<Vertex, int> PriorityQueue::top() {
    return pq.top();
}

size_t PriorityQueue::size() {
    return pq.size();
}

bool PriorityQueue::empty() {
    return pq.empty();
}

bool PriorityQueue::clear() {
    while (!pq.empty()) {
        pq.pop();
    }

    if (pq.size() == 0) {
        return true;
    }
    return false;
}