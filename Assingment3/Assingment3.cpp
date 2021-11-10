// File:   Bipartition.cpp
// Date:   Nov 8, 2021
// Author: Harshit Raj (harshitr20@iitk.ac.in)
// Author: Shubhan R (shubhanr20@iitk.ac.in)

#include <iostream>
using namespace std;

class AdjacencyList // it is the linked list that stores node index
{
public:
	// Structure of each node
	typedef struct Node
	{
		int adj; // index stored in the node
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

	// Append a node to the end of the list
	void add(int adj)
	{
		node *newNode = createNode(adj);
		node *last = nil->prev;

		newNode->prev = last;
		newNode->next = nil;
		last->next = nil->prev = newNode;
	}

	// frees up the list
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
	AdjacencyList *arr; // array of linked lists
	// N: number of nodes, E: number of edges
	int N, E;

	// Function adds the edge from v to w and w to v
	void addEdge(int v, int w)
	{
		arr[v].add(w); // adds edge (v,w) to the graph
		arr[w].add(v); // adds edge (w,v) also to the graph
		// we add both (v,w) and (w,v) to the graph as it is undirected
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
		// flag to check if the graph is bipartite or not and there is no discrepancy in set numbering
		bool ok = true;

		// stores what set nodes of adjacency list will be assigned (opposite set of node v)
		int altset = set[v] == 1 ? 2 : 1;

		// iterating over the adjacency list of v
		AdjacencyList::node *temp = arr[v].nil->next; // first node after sentinal node of adjacency list
		while (temp != arr[v].nil && ok)
		{
			// if the adjacency list node has no set assigned
			if (set[temp->adj] == -1)
			{
				set[temp->adj] = altset; // assign altset
				ok = ok && bipartitionUtil(temp->adj, set);
			}

			// if the adjacent node has same set as index v, it is contradiction and graph is not bipartite
			if (set[temp->adj] == set[v])
				return false;

			temp = temp->next;
		}

		return ok;
	}

	// bipartiton the graph
	void Bipartite()
	{
		// we represent each node belonging to 2 sets, 1 and 2 to check if graph is bipartite
		int set[N]; // array to store the set number of each node
		for (int i = 0; i < N; i++)
			set[i] = -1; // -1 represents it is still unassigned

		//  looping over the nodes
		for (int i = 0; i < N; i++)
		{
			// if the node does not have set assigned
			if (set[i] == -1)
			{
				// assign the node to set 1
				set[i] = 1;
				if (!bipartitionUtil(i, set)) // checks if any contradiction arises in the set assignment
				{
					cout << "NO" << endl;
					return;
				}
			}
		}

		// the graph is bipartite if it reaches this state
		cout << "YES" << endl;
		// printing the set of each node
		for (int i = 0; i < N; i++)
			cout << set[i] << endl;
	}

	// take input from stdin
	void input()
	{
		//  looping over the edges
		for (int i = 0; i < E; i++)
		{
			int v, w;
			cin >> v >> w;

			// just checks for invalid vertex index
			if (v < 0 || v >= N || w < 0 || w >= N)
			{
				cerr << "Invalid vertex" << endl;
				return;
			}

			// add the edge
			addEdge(v, w);
		}
	}

	// deletes the graph
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

	g.Bipartite();

	g.deleteGraph();

	return 0;
}
