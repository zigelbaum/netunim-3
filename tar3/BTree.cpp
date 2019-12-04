#include"BTree.h"
#include"BNode.h"

template <typename T>
T* BTree<T>::search(BNode<T> *p, T x)//search and return pointer to value 
{
	T* t = NULL;

	for (int i = 0; i < p->nkeys; i++)//goes through all values 
	{
		if (p->Key[i] == x)
			return p->Key[i];
	}
	for (int i = 0; i < p->nsons; i++)//goes through sons and calls the function on the son 
	{
		t = search(p->Son[i], x);

	}
	return t;
}


template <typename T>
void BTree<T>::printAllKeys(BNode<T> *p, std::function<bool(const T&)> predicate)
{

}

template <typename T>
void BTree<T>::deleteSubTree(BNode<T> * t)
{
	/*list<T> l = new list<T>;
	subtreeList(t,l);//gets all values
	while (!l.empty())
	{
	t->deleteVal(l.front());
	l.remove();
	}*/
	if (t)
	{
		for (int i = 0; i < t->nsons; i++)
			deleteSubTree(t->Son[i]);
		delete t;
	}

}

template <typename T>
void BTree<T>::printSubTree(BNode<T> *t)
{
	if (!t)
		return;
	int j = t->nsons;
	if (j == 0)//if leaf
		for (int i = 0; i < t->nkeys; i++)
		{
			cout << t->Key[i] << endl;
		}
	else
	{

		for (int i = 0; i < t->nkeys; i++)
		{
			printSubTree(t->Son[i]);
			cout << t->Key[i] << endl;

		}
		printSubTree(t->Son[t->nsons - 1]);
	}

}


template <typename T>
void BTree<T>::insert(T x) //add a value to the tree
{
	BNode<T> *tmp = NULL;
	T tx;
	if (root == NULL)
		root = new BNode<T>(x);
	else
	{
		root->insert(x, tx, tmp);
		if (tmp) //a split was done;
		{
			BNode<T> *newRoot = new BNode<T>(tx);
			newRoot->Son[0] = root;
			newRoot->Son[1] = tmp;
			root = newRoot;
		}
	}

}

template <typename T>
void BTree<T>::deleteVal(T x)
{
	T tmp;
	bool holeSent;
	if (root == NULL) return;
	root->deleteVal(x, false, tmp, holeSent); //and if a hole was return, the depth of all leaves reduces in one.
	if (holeSent == true)
		if (root->nsons == 1) //the son will be the root
		{
			BNode<T> *tmp = root;
			root = root->Son[0];
			delete tmp;
		}
	//otherwise, the root is allowed to have less than M/2 nodes.
}