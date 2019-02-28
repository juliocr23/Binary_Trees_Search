/*
 * BinaryTree.cpp
 *
 *  Created on: Oct 31, 2017
 *      Author: julio
 *     Purpose: The purpose of this file is to implement the BinaryTree.h functions
 */
#include "BinaryTree.h"
#include <iostream>

template<class T>
BinaryTree<T>:: BinaryTree(){
	root = 0;
}

template<class T>
BinaryTree<T>:: BinaryTree(const BinaryTree<T>& other){
	copy(root,other.root);
}

template<class T>
BinaryTree<T>:: ~BinaryTree(){
	eraseTree(root);

}

template<class T>
void BinaryTree<T>::operator =(const BinaryTree& other){
	eraseTree(root);
	copy(root,other.root);
}

template<class T>
void BinaryTree<T>:: inorder(BinaryTreeNode<T> *p, void(*visit) (T&,int&)) {
	if (p != 0){
		inorder(p->left, *visit);
		(*visit)(p->info,p->count);
		inorder(p->right, *visit);
	}
}

template<class T>
void BinaryTree<T>::preorder(BinaryTreeNode<T> *p, void(*visit) (T&,int&)) {
	if (p != 0){
		(*visit)(p->info,p->count);
		preorder(p->left,*visit);
		preorder(p->right,*visit);
	}
}

template<class T>
void BinaryTree<T>::postorder(BinaryTreeNode<T> *p, void(*visit) (T&,int&)) {
	if (p != 0){
		postorder(p->left,*visit);
		postorder(p->right,*visit);
		(*visit)(p->info,p->count);
	}
}
template<class T>
void BinaryTree<T>::inorder(void (*visit) (T&,int&)){
	inorder(root, *visit);
}

template<class T>
void BinaryTree<T>::preorder(void(*visit)(T&,int&)){
	preorder(root, *visit);
}

template<class T>
void BinaryTree<T>::postorder(void(*visit) (T&,int&)){
	postorder(root, *visit);
}
template<class T>
void BinaryTree<T>::eraseTree(BinaryTreeNode<T>*&p){
	if(p != 0){
		eraseTree(p->left);
		eraseTree(p->right);
		delete p;
		p = 0;
	}
}

template<class T>
void BinaryTree<T>::copy(BinaryTreeNode<T>* &original,
		  BinaryTreeNode<T>* other){

	if(other != 0){
		original = new BinaryTreeNode<T>;
		original->info = other->info;
		original->count = other->count;
		copy(original->left,other->left);
		copy(original->right,other->right);
	}
}