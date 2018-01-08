#pragma once

template <class T>
struct Edge;

template <class T>
struct Vertex;

template <class T>
struct Graph;

template <class T>
struct Edge
{
	int cost;
	bool hasVisited;
	Vertex<T>* to;
	Edge<T>* next;

	void initEdge(int newCost)
	{
		cost = newCost;
		to = NULL;
		next = NULL;
		hasVisited = false;
	}
};

template <class T>
struct Vertex
{
	T data;
	Vertex<T>* next;
	Edge<T>* firstEdge;

	void initVertex(T newData)
	{
		data = newData;
		next = NULL;
		firstEdge = NULL;
	}

	Edge<T>* getEdge(T searchData)
	{
		Edge<T>* walk = firstEdge;

		while(walk != NULL && walk->to->data != searchData)
		{
			walk = walk->next;
		}

		return walk;
	}

	bool containsEdge(T searchData)
	{
		if(getEdge(searchData) == NULL)
			return false;
		else
			return true;
	}
};

template <class T>
struct Graph
{
	Vertex<T> *firstVertex;

	void initGraph()
	{
		firstVertex = NULL;
	}

	void addVertex(T data)
	{
		Vertex<T>* newVertex = new Vertex<T>;
		newVertex->initVertex(data);

		newVertex->next = firstVertex;
		firstVertex = newVertex;

		//cout << "Vertex Added " << endl;
	}

	void addEdge(T to, T from, int cost = 0)
	{
		Vertex<T>* toWalk = firstVertex;

		while(toWalk != NULL && toWalk->data != to)
		{
			toWalk = toWalk->next;
		}

		if(toWalk == NULL)
		{
			addVertex(to);
			toWalk = firstVertex;
		}

		cout << "Found TO " << to << endl;

		Vertex<T>* fromWalk = firstVertex;

		while(fromWalk != NULL && fromWalk->data != from)
		{
			fromWalk = fromWalk->next;
		}

		if(fromWalk == NULL)
		{
			addVertex(from);
			fromWalk = firstVertex;
		}

		cout << "Found FROM" << from <<  endl;
		Edge<T>* newEdge = new Edge<T>;
		newEdge->initEdge(cost);

		newEdge->to = toWalk;
		newEdge->next = fromWalk->firstEdge;

		fromWalk->firstEdge = newEdge;

		cout << "Added Edge" << endl;
	}

	Vertex<T>* getVertex(T data)
	{
		Vertex<T>* walk = firstVertex;

		while(walk != NULL && walk->data != data)
		{
			walk = walk->next;
		}

		return walk;
	}

	bool contains(T data)
	{
		if(getVertex(data) == NULL)
			return false;
		else
			return true;
	}
};