/*
 * BSeachTree.h
 *
 *  Created on: Nov 2, 2017
 *      Author: Julio Rosario
 *     Purpose: The purpose of this class is to create a Binary search tree so that
 *               way we can perform binary search but on link lists instead of arrays. 
 */

#ifndef BSEARCH_H_
#define BSEARCH_H_
#include "BinaryTree.h"
#include "BinaryTree.cpp"

template<class T>
class BSearchTree: public BinaryTree<T>{
private:
	void deleteFromTree(BinaryTreeNode<T>*&p);
public:
	bool search(T);
	void insert(T);
	void deleteNode(T);
};
#endif /* BSEARCH_H_ */
