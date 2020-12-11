#include "priorityqueue.h"

/**
 * @brief Default constructor
 * 
 */
PriorityQueue::PriorityQueue() {
    //do nothing
}

/**
 * @brief Constructor
 * 
 * @param s, the starting vertex
 */
PriorityQueue::PriorityQueue(Vertex& s) {
    pq.push(std::make_pair(s, 0));
}s

/**
 * @brief Push a new pair onto the queue
 *        (May be a duplicate, but will have
 *         a smaller distance)
 * 
 * @param p 
 */
void PriorityQueue::push(std::pair<Vertex, int> p) {
    pq.push(p);
}

/**
 * @brief Removes the top element in the priority queue
 * 
 * @return std::pair<Vertex, int>, the top element in the min-heap 
 *         that is being removed
 */
std::pair<Vertex, int> PriorityQueue::pop() {
    std::pair<Vertex, int> t = pq.top();
    pq.pop();
    return t;
}

std::pair<Vertex, int> PriorityQueue::top() {
    return pq.top();
}

/**
 * @brief Returns the size of priority queue
 * 
 * @return size_t 
 */
size_t PriorityQueue::size() {
    return pq.size();
}

/**
 * @brief Determines if priority queue is empty
 * 
 * @return true, if empty
 * @return false, if not empty
 */
bool PriorityQueue::empty() {
    return pq.empty();
}

/**
 * @brief Pops all remaining values in priority queue
 * 
 * @return true, if successfully remove all elements
 * @return false otherwise
 */
bool PriorityQueue::clear() {
    while (!pq.empty()) {
        pq.pop();
    }

    if (pq.size() == 0) {
        return true;
    }
    return false;
}