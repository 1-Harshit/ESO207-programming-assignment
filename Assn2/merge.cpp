void Merge(TwoThreeTree<T> S1, TwoThreeTree<T> S2)
{
	int h1 = 0, h2 = 0;        // heights of tree
	int min1, min2;            // mimimum of both trees
	
	min1, h1 = GetHeightAndMin(S1);
	min2, h2 = GetHeightAndMin(S2);
	
	if (S1.root->type == nil) { // when S1 is empty tree
		root = S2.root;
		return;
	}
	if (S2.root->type == nil) { // when S2 is empty tree
		root = S1.root;
		return;
	}

	if (h1 == h2)
	{
		root = newtwonode(min2, S1.root, S2.root);
		return;
	}

	if (h1 > h2) // insert S2 inside S1
	{
		insrtn rn = InsertRightNode(S1.root, S2.root, h1, h2, min2);
		if (rn.n2->type == nil)
		{
			root = rn.n1;
		}
		else
		{
			root = newtwonode(rn.val, rn.n1, rn.n2);
		}
	}
	else if (h1 < h2)
	{
		insrtn rn = InsertLeftNode(S1.root, S2.root, h1, h2, min2);
		if (rn.n2->type == nil)
		{
			root = rn.n1;
		}
		else
		{
			root = newtwonode(rn.val, rn.n1, rn.n2);
		}
	}
}