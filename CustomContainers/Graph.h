#pragma once

#include <iostream>
#include "Vector.h"

template<typename T> 
class Graph
{
public:
	struct Node
	{
		//data stored in graph
		const T* data;
		// used for graph traversal
		bool isVisited;
		// used for graph traversal
		//if looking for end node can be used to obtain a path to the start
		int fromNode = -1;
		//edges connected to the node
		Vector<Node*> edges;

	};

public:
	Graph() {}

	~Graph()
	{
		Terminate();
	}

	int AddItem(const T* data)
	{
		Node* newNode = new Node();
		newNode->data = data;
		newNode->isVisited = false;
		mNodes.PushBack(newNode);

		return mNodes.Size() - 1;
	}

	void AddLink(int a, int b)
	{
		if (a < 0 || a >= mNodes.Size() || b < 0 || b >= mNodes.Size())
		{
			return;
		}
		mNodes[a]->edges.PushBack(b);
		mNodes[b]->edges.PushBack(a);
		
		
	}

	void GetAllConnectionDFS(int startIndex, Vector<T*>& connections)
	{

	}

	void GetAllConnectionsBFS(int startIndex, Vector<T*>& connections)
	{

	}

	void GetPathDFS(int startIndex, int endIndex, Vector<*T>& path)
	{

	}

	void GetPathBFS(int startIndex, int endIndex, Vector<*T> path)
	{

	}

	void Terminate()
	{
		for (std::size_t i = 0; i < mNodes.Size(); ++i)
		{
			delete mNodes[i];
			mNodes[i] = nullptr;

		}
		mNodes.Clear();
	}




private:
	
	void Reset()
	{
		for (std::size_t i = 0; i < mNodes.Size(); ++i)
		{
			mNodes[i]->isVisited = false;
		}
	}

	Vector<Node*> mNodes;

};