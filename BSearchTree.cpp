/*
 * BSearch.cpp
 *
 *  Created on: Nov 2, 2017
 *      Author: julio
 *      Purpose: The purpose of this file is to implement the BSearchTree.h functions
 */

#include "BSearchTree.h"
#include <iostream>
template<class T>
bool BSearchTree<T>:: search(T item){

	BinaryTreeNode<T>* p =root;
	bool found = false;
	while(p != 0 && !found){
		if(p->info == item)
			found = true;
		else if(p->info>item)
			p = p->left;
		else
			p = p->right;
	}
	return found;
}

template<class T>
void BSearchTree<T>::insert(T item){

	//Create the new node for the new element.
	BinaryTreeNode<T>* newItem;
	newItem = new BinaryTreeNode<T>;
	newItem->info = item;
	newItem->count++;
	newItem->left = 0;
	newItem->right = 0;

	if (root == 0) {
		root = newItem;
	}
	else{

		BinaryTreeNode<T>* p = root;
		BinaryTreeNode<T>* before = p;

		//Search the spot where to insert item
		while(p != 0){
			before = p;
			if(p->info == item){
				p->count++;
				delete newItem;
				newItem = 0;
				return;
			}else if(p->info >item){
				p = p->left;
			}else{
				p = p->right;
			}
		}

		//Insert to the left if it is greater than info
		//other wise insert it to the right
		if (before->info > item) 
			before->left = newItem;
		else if(before->info < item)
			before->right = newItem;
	}
}

template<class T>
void BSearchTree<T>:: deleteFromTree(BinaryTreeNode<T>*&p){

	BinaryTreeNode<T>* traverse;	//Pointer to traverse the tree
	BinaryTreeNode<T>* before;      //Pointer behind traverse
	BinaryTreeNode<T>* temp;        //pointer to delete node

	if(p == 0)
		std::cerr<< "Error: The node to be deleted is NULL." << std::endl;
	else if(p->left == 0 && p->right == 0){
		temp = p;
		p = 0;
		delete temp;
	}else if(p->left == 0){
		temp = p;
		p = temp->right;
		delete temp;
	}else if(p->right == 0){
		temp = p;
		p = temp->left;
		delete temp;
	}else{
		traverse = p->left;
		before = 0;

		while(traverse ->right != 0){
			before = traverse;
			traverse = traverse->right;
		}
		p->info = traverse->info;

		if(before == 0)
			p->left = traverse->left;
		else
			before->right = traverse->left;

		delete traverse;
	}
}

template<class T>
void BSearchTree<T>:: deleteNode(T item){
	BinaryTreeNode<T>*traverse;
	BinaryTreeNode<T>* before;
	bool found = false;
	if(root == 0)
		std::cout << "Cannot delete from empty tree." << std::endl;
	else
	{
		traverse = root;
		before = root;

		while(traverse != 0 && !found){
			if(traverse->info == item)
				found = true;
			else{
				before = traverse;
				if(traverse->info >item)
					traverse = traverse->left;
				else
					traverse = traverse->right;
			}
		}

		if(traverse == 0)
			std::cout << "The delete item is not in the tree." << std::endl;
		else if(found){
			if(traverse == root)
				deleteFromTree(root);
			else if(before->info >item)
				deleteFromTree(before->left);
			else
				deleteFromTree(before->right);
		}
	}
}