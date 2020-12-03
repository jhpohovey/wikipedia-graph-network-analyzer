/* Your code here! */
#include "dsets.h"

/**
 * @brief Construct a new Disjoint Sets:: Disjoint Sets object
 * 
 */
DisjointSets::DisjointSets() {}

/**
 * @brief Construct a new Disjoint Sets:: Disjoint Sets object
 * 
 * @param elems 
 */
DisjointSets::DisjointSets(std::vector<int> elems) {
    elems_ = elems;
}

/**
 * @brief Creates n unconnected root nodes at the end of the vector.
 * 
 * @param num, The number of nodes to create
 */
void DisjointSets::addelements(int num) {

    elems_.reserve(num);
    for (int i = 0; i < num; ++i) {
        elems_.push_back(-1);
    }
}

/**
 * @brief This function should compress paths and works as described in lecture.
 * 
 * @param elem 
 * @return The index of the root of the up-tree in which the parameter element resides.
 */
int DisjointSets::find(int elem) {

    if (elems_[elem] < 0) { //base case - we have found the root
        return elem;
    }
    else { //otherwise, recurse and update the parent to be the new poss root
        int root = find(elems_[elem]);
        elems_[elem] = root;
        return root;
    }
}

/**
 * @brief This function should be implemented as union-by-size. That is, when you setunion 
 * two disjoint sets, the smaller (in terms of number of nodes) should point at the larger. 
 * This function works as described in lecture, except that you should not assume that the 
 * arguments to setunion are roots of existing uptrees. Your setunion function SHOULD find 
 * the roots of its arguments before combining the trees. If the two sets are the same size, 
 * make the tree containing the second argument point to the tree containing the first. (Note 
 * that normally we could break this tie arbitrarily, but in this case we want to control 
 * things for grading.
 * 
 * @param a, index of the first element to union
 * @param b, index of the second element to union
 */
void DisjointSets::setunion(int a, int b) {

    int root1 = find(a);
    int root2 = find(b);

    int newSize = elems_[root1] + elems_[root2];

    //if elemant at a is less than element at b (ie more negative), root at a is the larger set
    //so, therefore, we union the smaller set b, with a
    if (elems_[root1] <= elems_[root2]) {
        elems_[root2] = root1;
        elems_[root1] = newSize;
    }
    //do reverse if opposite is true
    else {
        elems_[root1] = root2;
        elems_[root2] = newSize;
    }
}

/**
 * @brief This function should return the number of nodes in the up-tree containing the element.
 * 
 * @param elem 
 * @return number of nodes in the up-tree containing the element
 */
int DisjointSets::size(int elem){
    return std::abs(elems_[find(elem)]);
}


