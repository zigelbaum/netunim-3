#include"BNode.h"
template <typename T>
BNode<T>::BNode()
{
	nsons = 0; nkeys = 0;
	for (int i = 0; i < M; i++)
		Son[i] = NULL;
}

template <typename T>
BNode<T>::BNode(T x) //initialize as a leaf
{
	nsons = 2; nkeys = 1;
	Key[0] = x;
	for (int i = 0; i < M; i++)
		Son[i] = NULL;
}

template <typename T>
void BNode<T>::AddValue(T x, BNode<T> *pnew, T &upx, BNode<T>*& upt) //add from lower level
{
	int i;
	T v[M];
	BNode<T>* p[M + 1];

	p[0] = Son[0];
	for (i = 0; i < nsons - 1 && Key[i] < x; i++)
	{
		v[i] = Key[i];
		p[i + 1] = Son[i + 1];
	}
	v[i] = x;
	p[i + 1] = pnew;
	for (; i < nsons - 1; i++)
	{
		v[i + 1] = Key[i];
		p[i + 2] = Son[i + 1];
	}
	nsons++; nkeys++;
	if (nsons > M) //a split required
	{
		int half = nsons / 2;
		Son[0] = p[0];
		for (i = 0; i < half - 1; i++)
		{
			Key[i] = v[i];
			Son[i + 1] = p[i + 1];
		}
		upx = v[half - 1];
		upt = new BNode<T>;
		upt->Son[0] = p[half];
		for (i = half; i < M; i++)
		{
			upt->Key[i - half] = v[i];
			upt->Son[i + 1 - half] = p[i + 1];
		}
		nsons = half; //after the splitting
		nkeys = nsons - 1;
		upt->nsons = M + 1 - nsons; //the rest
		upt->nkeys = upt->nsons - 1; //the rest
	}
	else //no spliting
	{
		Son[0] = p[0];
		for (i = 0; i < nsons - 1; i++)
		{
			Key[i] = v[i];
			Son[i + 1] = p[i + 1];
		}
		//upx = 0;
		upt = NULL;
	}
}

template <typename T>
void BNode<T>::insert(T x, T &valup, BNode<T>*& pointup) //returns the left pointer if a split was done, or NULL;
{
	T tmp;
	BNode<T> *tmpp = NULL;
	pointup = NULL; //no split done here yet.
	if (Son[0] == NULL) //a leaf
	{
		AddValue(x, NULL, valup, pointup);
	}
	else
	{
		for (int i = 0; i < nkeys; i++)
		{
			if (x < Key[i])
			{
				Son[i]->insert(x, tmp, tmpp);
				break;
			}
		}
		if (x >= Key[nkeys - 1])
			Son[nsons - 1]->insert(x, tmp, tmpp);
		if (tmpp) //a split was done, with value tmp and pointer tmpp
		{
			AddValue(tmp, tmpp, valup, pointup); //add the added value to current level. If required, split.

		}
	}


}


template <typename T>void BNode<T>::DeleteFirst(T &val, BNode<T>* &firstSubTree) //delete the first in the node. returns the value deleted and the first SubTree
{
	val = Key[0];
	firstSubTree = Son[0];
	for (int i = 0; i < nsons - 2; i++)
	{
		Key[i] = Key[i + 1];
		Son[i] = Son[i + 1];
	}
	Son[nsons - 2] = Son[nsons - 1]; //copy last subtree
	nsons--; nkeys--;
}

template <typename T>
void BNode<T>::DeleteLast(T &val, BNode<T>* &lastSubTree) //delete the first in the node. returns the value deleted and the first SubTree
														  //move one value and some tree to a brother
{
	val = Key[nsons - 2]; //last value
	lastSubTree = Son[nsons - 1];
	Son[nsons - 1] = NULL;
	nsons--; nkeys--;
}

template <typename T>
void BNode<T>::DeleteValueFromLeaf(int ToDelete) //delete a value from a leaf
{
	for (int i = ToDelete; i < nsons - 2; i++)
		Key[i] = Key[i + 1];
	nsons--; nkeys--;
}

template <typename T>
void BNode<T>::unifyWith(int brotherInd, int HoleInd)
//unify values and pointers with values and pointers of Son[brotherInd], and then delete Son[brotherInd]
{
	BNode<T> *brother = Son[brotherInd];
	BNode<T> *holeNode = Son[HoleInd];
	int i;
	if (brotherInd < HoleInd)
	{
		//move sons and values from the hole to the brother
		brother->Key[brother->nsons - 1] = Key[brotherInd];
		for (i = 0; i < holeNode->nsons - 1; i++)
		{
			brother->Son[brother->nsons + i] = holeNode->Son[i];
			brother->Key[brother->nsons + i] = holeNode->Key[i];
		}
		brother->Son[brother->nsons + holeNode->nsons - 1] = holeNode->Son[holeNode->nsons - 1];
		brother->nsons += holeNode->nsons;
		brother->nkeys = brother->nsons - 1;
		//delete the hole and remove it from the tree
		delete holeNode;
		for (i = HoleInd; i < nsons - 1; i++)
		{
			Son[i] = Son[i + 1];
			Key[i - 1] = Key[i];
		}
		nsons--; nkeys--;
	}
	else //HoleInd < brotherInd
	{
		//move sons and values from the brother to the hole
		holeNode->Key[holeNode->nsons - 1] = Key[HoleInd];
		for (i = 0; i < brother->nsons - 1; i++)
		{
			holeNode->Son[holeNode->nsons + i] = brother->Son[i];
			holeNode->Key[holeNode->nsons + i] = brother->Key[i];
		}
		holeNode->Son[holeNode->nsons + brother->nsons - 1] = brother->Son[brother->nsons - 1];
		holeNode->nsons += brother->nsons;
		holeNode->nkeys = holeNode->nsons - 1;
		//delete the hole and remove it from the tree
		delete brother;
		for (i = brotherInd; i < nsons - 1; i++)
		{
			Son[i] = Son[i + 1];
			Key[i - 1] = Key[i];
		}
		nsons--; nkeys--;
	}
}


template <typename T>
void BNode<T>::moveToSubtreeFromBrother(int subTree, int subTreeBrother) //move one value and one subtree from subTreeBrother to subTree 
{
	BNode<T> *brother = Son[subTreeBrother];
	BNode<T> *holeNode = Son[subTree];
	if (subTreeBrother < subTree)
		//larger value from subTreeBrother should be moved to father, and value from father should be moved to subTree
	{
		T valToFather = brother->Key[brother->nsons - 2];
		T valToSon = Key[subTreeBrother];
		Key[subTreeBrother] = valToFather;
		for (int i = 0; i < holeNode->nsons - 1; i++)
		{

			holeNode->Son[i + 1] = holeNode->Son[i];
			holeNode->Key[i + 1] = holeNode->Key[i];
		}
		holeNode->Son[holeNode->nsons] = holeNode->Son[holeNode->nsons - 1];
		holeNode->Key[0] = valToSon;
		holeNode->Son[0] = brother->Son[brother->nsons - 1]; //the last son of the brother is moved to the hole.
															 //and number of sons in father is not changed.
	}
	else
		//smallest value from subTreeBrother should be moved to father
	{
		T valToFather = brother->Key[0];
		T valToSon = Key[subTree];
		BNode<T> *ChildToSon = brother->Son[0];
		Key[subTree] = valToFather;

		for (int i = 0; i < brother->nsons - 2; i++)
		{
			brother->Son[i] = brother->Son[i + 1];
			brother->Key[i] = brother->Key[i + 1];
		}
		brother->Son[brother->nsons - 2] = brother->Son[brother->nsons - 1];
		holeNode->Key[holeNode->nsons - 1] = valToSon;
		holeNode->Son[holeNode->nsons] = ChildToSon; //the last son of the brother is moved to the hole.
													 //and number of sons in father is not changed.
	}
	holeNode->nsons++; holeNode->nkeys++;
	brother->nsons--; brother->nkeys--;
}

template <typename T>
int BNode<T>::indexValInK(T x)
{
	for (int i = 0; i < nsons - 1; i++)
		if (Key[i] == x)
			return i;
	return -1;
}

template <typename T>
int BNode<T>::indexValGEQInK(T x) //index of value greater or equal to x
{
	for (int i = 0; i < nsons - 1; i++)
		if (Key[i] >= x) return i;
	return (nsons - 1); //x is larger than all values
}

template <typename T>
void BNode<T>::deleteVal(T x, bool searchForSuccessor, T&successorFound, bool& holeSent)
//delete a value x from the subtree started with this BNode.
{
	T sufF;
	bool holeFound = false;
	BNode<T> *tmp;
	int subTreeInd = -1;
	holeSent = false;
	if (Son[0] == NULL) //in a leaf
	{
		if (searchForSuccessor)
		{
			DeleteFirst(successorFound, tmp);
			if (sonsUnderMinimum())
			{
				holeSent = true;
			}
			return;
		}
		else //remove value x from tree
		{
			int indOfSon = indexValInK(x);
			if (indOfSon >= 0) //x found in the leaf
			{
				DeleteValueFromLeaf(indOfSon);
				if (sonsUnderMinimum()) //and now under the minimum
				{
					holeSent = true;
				}
				return;
			}
		}
		return; //value x not found.
	}
	else if (searchForSuccessor == false) //if this is not a leaf
	{
		holeFound = false;
		int indfound = indexValGEQInK(x);
		if (indfound >= 0 && indfound <nsons - 1 && Key[indfound] == x) //value found in tree. delete its successor
		{
			Son[indfound + 1]->deleteVal(x, true, sufF, holeFound); //delete the successor of x in the subtree right to it.
			subTreeInd = indfound + 1;
			Key[indfound] = sufF; //***change value to the value of the successor***
		}
		else if (indfound >= 0)//search for x in Son[indfound+1]
		{
			Son[indfound]->deleteVal(x, false, sufF, holeFound); //search for x in subtree # (indfound+1)
			subTreeInd = indfound;
		}
		else //no such index found. x is the largest value. Search for it in last subtree
		{
			Son[nsons - 1]->deleteVal(x, false, sufF, holeFound); //search for x in subtree # (indfound+1)
			subTreeInd = nsons - 1;
		}

	}
	else //continue to search the search for successor
	{
		holeFound = false;
		Son[0]->deleteVal(x, true, successorFound, holeFound); //search for the successor and returns it.
		subTreeInd = 0;
	}

	//if x found and hole found, has to continue.
	int brotherInd = -1;
	if (holeFound) //a hole exists in subTree
	{
		if (subTreeInd == 0 && Son[subTreeInd + 1]->sonsMinimum())
			brotherInd = subTreeInd + 1;

		else if (subTreeInd == nsons - 1 && Son[subTreeInd - 1]->sonsMinimum())
			brotherInd = subTreeInd - 1;

		else if (subTreeInd>0 && subTreeInd<nsons - 1 && Son[subTreeInd - 1]->sonsMinimum() && Son[subTreeInd + 1]->sonsMinimum())
			brotherInd = subTreeInd - 1;

		if (sonsMinimum()) //parent has minimum values
		{
			if (brotherInd >= 0)    //CASE 1: brother has minimum values: has to unify brother with parent.
			{
				unifyWith(brotherInd, subTreeInd);
				holeSent = true;
				return;
			}
			else //CASE 2:father with minimum value, brother with larger value.
			{
				if (subTreeInd == 0)
					brotherInd = subTreeInd + 1;

				else if (Son[subTreeInd - 1]->sonsMoreThanMinimum())
					brotherInd = subTreeInd - 1;
				else
					brotherInd = subTreeInd + 1;

				//rent a value from brotherInd to subTreeInd
				moveToSubtreeFromBrother(subTreeInd, brotherInd);

				holeSent = false;
				return;
			}

		}
		else //father with larger value
		{
			if (brotherInd >= 0)    //CASE 3: brother has minimum values: has to unify brother with hole.
			{
				unifyWith(brotherInd, subTreeInd);
				holeSent = false;
				return;
			}
			else //CASE 4: brother with larger value. has to rent
			{
				if (subTreeInd == 0)
					brotherInd = subTreeInd + 1;

				else if (Son[subTreeInd - 1]->sonsMoreThanMinimum())
					brotherInd = subTreeInd - 1;
				else
					brotherInd = subTreeInd + 1;

				//rent a value from brotherInd to subTreeInd
				moveToSubtreeFromBrother(subTreeInd, brotherInd);

				holeSent = false;
				return;
			}


		} //father with larger value
	} //if holefound

}

