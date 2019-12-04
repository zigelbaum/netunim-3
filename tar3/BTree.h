#pragma once
#include"BNode.h"
template <typename T>
class BTree
	//BTree with max degree M
{
	BNode<T> *root;
public:
	BTree() { root = NULL; } //build an empty tree
	~BTree() { deleteTree(); }
	void insert(T x);      //add a value to the tree
	void deleteVal(T x);
	void deleteSubTree(BNode<T> *t);
	void deleteTree() { deleteSubTree(root); }
	void printSubTree(BNode<T> *t);
	void printTree() { printSubTree(root); }
	void printAllKeys(std::function<bool(const T&)> predicate) { printAllKeys(root, predicate); }
	void printAllKeys(BNode<T> *p, std::function<bool(const T&)>);
	T* search(T x) { return search(root, x); }
	T* search(BNode<T> *p, T x);


};