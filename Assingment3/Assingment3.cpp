// File:   Bipartition.cpp
// Date: Nov 8, 2021
// Author: Harshit Raj (harshitr20@iitk.ac.in)
// Author: Shubhan R (shubhanr20@iitk.ac.in) 

#include<iostream>
using namespace std;

class AdjacencyList
{
public:
	// Structure of each node
	typedef struct Node
	{
		int adj;
		struct Node *next;
		struct Node *prev;
	} node;

	// Creading a node and returning it
	node *createNode(int adj)
	{
		node *newNode = new node;
		newNode->adj = adj;
		newNode->next = newNode->prev = NULL;
		return newNode;
	}

	node *nil; // Sentinal node

	// Constructor intializing the sentinal node
	AdjacencyList()
	{
		nil = createNode(-1);
		nil->next = nil->prev = nil;
	}

	// Append a node in the end of the list
	void add(int adj)
	{
		node *newNode = createNode(adj);
		node *last = nil->prev;

		newNode->prev = last;
		newNode->next = nil;
		last->next = nil->prev = newNode;
	}

	// delete the list
	void deleteList()
	{
		node *temp = nil->next;
		while (temp != nil)
		{
			node *next = temp->next;
			delete temp;
			temp = next;
		}
		nil->next = nil->prev = nil;
	}
};

// graph class
class Graph
{
private:
	AdjacencyList *arr;
	int N, E;

	// Function adds the edge from u to v
	void addEdge(int v, int w)
	{
		arr[v].add(w);
		arr[w].add(v);
	}

public:
	// Constructor
	Graph(int v, int e)
	{
		N = v;
		E = e;
		arr = new AdjacencyList[N];
	}

	// bipartition utility function
	bool bipartitionUtil(int v, int set[])
	{
		bool ok = true;
		int altset = set[v] == 1 ? 2 : 1;

		AdjacencyList::node *temp = arr[v].nil->next;
		while (temp != arr[v].nil)
		{
			if (set[temp->adj] == -1)
			{
				set[temp->adj] = altset;
				ok = ok && bipartitionUtil(temp->adj, set);
			}
			else if (set[temp->adj] == set[v])
				return false;
			temp = temp->next;
		}

		return ok;
	}

	// bipartiton the graph
	void bipartition()
	{
		int set[N];
		for (int i = 0; i < N; i++)
			set[i] = -1;

		for (int i = 0; i < N; i++)
		{
			if (set[i] == -1)
			{
				set[i] = 1;
				if (!bipartitionUtil(i, set))
				{
					cout << "NO" << endl;
					return;
				}
			}
		}

		cout << "YES" << endl;
		for (int i=0; i<N; i++)
			cout << set[i] << endl;
	}

	// take input from stdin
	void input()
	{
		for (int i = 0; i < E; i++)
		{
			int v, w;
			cin >> v >> w;

			if (v < 0 || v >= N || w < 0 || w >= N)
			{
				cerr << "Invalid vertex" << endl;
				return;
			}
			addEdge(v, w);
		}
	}

	// delete the graph
	void deleteGraph()
	{
		for (int i = 0; i < N; i++)
			arr[i].deleteList();
		delete[] arr;
		N = E = 0;
	}

};



int main()
{
	int V, E;
	cin >> V >> E;

	Graph g(V, E);
	g.input();

	g.bipartition();

	g.deleteGraph();

	return 0;
}
