/*
 * BinaryTree.h
 *
 *  Created on: Oct 31, 2017
 *      Author: Julio Rosario
 *     Purpose: The purpose of this class is to create the data structure of a tree
 *               so that we can implement other types of tree such as binary etc.
 */

#ifndef BINARYTREE_H_
#define BINARYTREE_H_

template<class T>
struct BinaryTreeNode{
	T info;
	int count = 0;
	BinaryTreeNode<T>*left;
	BinaryTreeNode<T>*right;
};

template<class T>
class BinaryTree{

protected:
	BinaryTreeNode<T>* root;
	void inorder(BinaryTreeNode<T> *p, void(*visit) (T&,int&));    //Return the info in inorder
	void preorder(BinaryTreeNode<T> *p, void(*visit) (T&,int&));   //Return the info in preorder
	void postorder(BinaryTreeNode<T> *p, void(*visit) (T&,int&));  //Return the info in postorder

	void copy(BinaryTreeNode<T>* &original,
			  BinaryTreeNode<T>* other);						   //Copy binary tree

	void eraseTree(BinaryTreeNode<T>*&);   						   //erase tree
public:
	BinaryTree();							                      //Constructor
	~BinaryTree();                                               //Destructor

	BinaryTree(const BinaryTree<T>&);                            //Copy constructor
	void operator=(const BinaryTree<T>&);                        //overloaded operator equal

	void inorder(void(*visit)(T&,int&));                         //Return the info and count in inorder
	void preorder(void(*visit)(T&,int&));                        //Return the info and count in preorder
	void postorder(void(*visit)(T&,int&));                       //Return the info and count in postorder
};



#endif /* BINARYTREE_H_ */
