// File: source.cpp
// Author: Shubhan R (shubhanr20@iitk.ac.in) 
// Author: Harshit Raj (harshitr20@iitk.ac.in)
#include <iostream>
#include <queue>

using namespace std;

// Alias function to create a leaf node
#define MakeSingleton newLeaf

enum nodeType // node types
{
	nil,
	leaf,
	twonode,
	threenode
};

// Node structure
struct two3node {
	nodeType type;
	int val; // only for leaf node--holds value
	int val1, val2; // it is min1, min2
	two3node *left, * mid, * right;
};

/* 
	FUCNTIONS TO CREATE NEW NODES 
	*newNilNode
	*newLeaf
	*newTwoNode
	*newThreeNode
*/

two3node *newNilNode() {
	two3node *node = new two3node;
	node -> val = node -> val1 = node -> val2 = 0;
	node -> type = nil;
	node -> left = node -> mid = node -> right = NULL;
	return node;
}

two3node *newLeaf(int val) {
	two3node *node = new two3node;
	node -> type = leaf;
	node -> val = val;
	node -> val1 = node -> val2 = 0;
	node -> left = node -> mid = node -> right = NULL;
	return node;
}

two3node *newTwoNode(int val, two3node *left, two3node *right) {
	two3node *node = new two3node;
	node -> type = twonode;
	node -> val1 = val;
	node -> val = node -> val2 = 0;
	node -> left = left;
	node -> mid = NULL;
	node -> right = right;
	return node;
}

two3node *newThreeNode(int MinLeft, int MinRight, two3node *left, two3node *mid, two3node *right) {
	two3node *node = new two3node;
	node -> type = threenode;
	node -> val1 = MinLeft;
	node -> val2 = MinRight;
	node -> val = 0;
	node -> left = left;
	node -> mid = mid;
	node -> right = right;
	return node;
}

// Helper: a returns type for function containing 
// 3 values i.e. 2 two3node and 1 value 
class insrtn {
public:
	int val;
	two3node *n2;
	two3node *n1;
	insrtn(two3node *nd1, two3node *nd2, int v) {
		n1 = nd1;
		n2 = nd2;
		val = v;
	}
};

two3node *nilnodespl = newNilNode(); // acts as special node of type nil in the following functions

/* 
	HELPER FUNCTION for merge function
	*InsertRightNode
	*InsertLeftNode
*/

insrtn InsertRightNode(two3node *r1, two3node *r2, int h1, int h2, int min2) {
	if (h1 == h2) {
		return insrtn(r1, r2, min2);
	}

	insrtn rn = InsertRightNode(r1 -> right, r2, h1 - 1, h2, min2);

	if (rn.n2 -> type == nil) {
		r1 -> right = rn.n1;
		return insrtn(r1, nilnodespl, 0);
	} else {
		if (r1 -> type == twonode) {
			return insrtn(newThreeNode(r1 -> val1, rn.val, r1 -> left, rn.n1, rn.n2), nilnodespl, 0);
		} else if (r1 -> type == threenode) {
			return insrtn(newTwoNode(r1 -> val1, r1 -> left, r1 -> mid), newTwoNode(rn.val, rn.n1, rn.n2), r1 -> val2);
		}
	}
	return insrtn(nilnodespl, nilnodespl, 0);
}
insrtn InsertLeftNode(two3node *r1, two3node *r2, int h1, int h2, int min2) {
	if (h1 == h2) {
		return insrtn(r1, r2, min2);
	}

	insrtn rn = InsertLeftNode(r1, r2 -> left, h1, h2 - 1, min2);

	if (rn.n2 -> type == nil) {
		r2 -> left = rn.n1;
		return insrtn(r2, nilnodespl, 0);
	} else {
		if (r2 -> type == twonode) {
			return insrtn(newThreeNode(rn.val, r2 -> val1, rn.n1, rn.n2, r2 -> right), nilnodespl, 0);
		} else if (r2 -> type == threenode) {
			return insrtn(newTwoNode(rn.val, rn.n1, rn.n2), newTwoNode(r2 -> val2, r2 -> mid, r2 -> right), r2 -> val1);
		}
	}
	return insrtn(nilnodespl, nilnodespl, 0);
}

/* 
	MERGE FUNCTION
	Merge two trees where elements of second tree
	are strictly greater than elements of first tree
*/
two3node *Merge(two3node *S1, two3node *S2) {
	if (S1 -> type == nil) // when S1 is empty tree
	{
		return S2;
	}
	if (S2 -> type == nil) // when S2 is empty tree
	{
		return S1;
	}

	int h1 = 0, h2 = 0; // heights of tree
	int min1, min2; // mimimum of both trees
	two3node *yo = S1; // dummy pointer to to find height and min

	while (yo -> type != leaf) {
		yo = yo -> left;
		h1++;
	}
	min1 = yo -> val;
	
	yo = S2;
	while (yo -> type != leaf) {
		yo = yo -> left;
		h2++;
	}
	min2 = yo -> val;

	if (h1 == h2) {
		return newTwoNode(min2, S1, S2);
	} else if (h1 > h2) { // insert S2 inside S1
		insrtn rn = InsertRightNode(S1, S2, h1, h2, min2);
		if (rn.n2 -> type == nil) {
			return rn.n1;
		} else {
			return newTwoNode(rn.val, rn.n1, rn.n2);
		}
	} else if (h1 < h2) {
		insrtn rn = InsertLeftNode(S1, S2, h1, h2, min2);
		if (rn.n2 -> type == nil) {
			return rn.n1;
		} else {
			return newTwoNode(rn.val, rn.n1, rn.n2);
		}
	}
}

void Extract(two3node *Tree) {
	if (Tree -> type == nil) {
		return;
	}

	queue < two3node *> nodes;
	nodes.push(Tree);

	while (!nodes.empty()) {
		two3node *temp = nodes.front();
		if (temp -> type == nil) {
			cerr << "this shouldn't have happened";
			return;
		} else if (temp -> type == leaf) {
			cout << temp -> val << " ";
		} else if (temp -> type == twonode) {
			nodes.push(temp -> left);
			nodes.push(temp -> right);
		} else if (temp -> type == threenode) {
			nodes.push(temp -> left);
			nodes.push(temp -> mid);
			nodes.push(temp -> right);
		}
		nodes.pop();
	}
	cout << endl;
	return;
}

void test() {
	two3node *S1, * S2, * S;
	S = newNilNode();

	S1 = MakeSingleton(1);
	for (int i = 2; i <= 500 ; i++) {
		S1 = Merge(S1, MakeSingleton(i));
	}

	S2 = MakeSingleton(777);
	for (int i = 778; i <= 1000; i++) {
		S2 = Merge(S2, MakeSingleton(i));
	}

	S = Merge(S1, S2);

	Extract(S);
}

int main() {
	test();
	return 0;
};
