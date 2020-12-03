/* Your code here! */
#pragma once

#include <vector>
#include <iostream>


class DisjointSets {
    public: 
        /* Default Constructor for DisjointSets class */
        DisjointSets();

        /* Constructor for DisjointSets class */
        DisjointSets(std::vector<int> elems);

        /**
         * @brief Construct a new Disjoint Sets:: Disjoint Sets object
         * 
         * @param elems 
         */
        void addelements(int num);

        /**
         * @brief This function should compress paths and works as described in lecture.
         * 
         * @param elem 
         * @return The index of the root of the up-tree in which the parameter element resides.
         */
        int find(int elem);

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
        void setunion(int a, int b);

        /**
         * @brief This function should return the number of nodes in the up-tree containing the element.
         * 
         * @param elem 
         * @return number of nodes in the up-tree containing the element
         */
        int size(int elem);
    
    private:
        std::vector<int> elems_;
        
};
