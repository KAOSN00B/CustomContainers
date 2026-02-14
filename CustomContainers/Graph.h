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
		Vector<int> edges;

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

	void GetAllConnectionDFS(int startIndex, Vector<const T*>& connections)
	{
		if (startIndex < 0 || startIndex >= mNodes.Size())
			return;

		Reset();

		Vector<Node*> stack;
		stack.PushBack(mNodes[startIndex]);

		while (stack.Size() > 0)
		{
			Node* node = stack[stack.Size() - 1];
			stack.PopBack();

			if (!node->isVisited)
			{
				node->isVisited = true;
				connections.PushBack(node->data);

				for (std::size_t i = 0; i < node->edges.Size(); ++i)
				{
					Node* next = mNodes[node->edges[i]];
					if (!next->isVisited)
						stack.PushBack(next);
				}
			}
		}
	}


	void GetAllConnectionsBFS(int startIndex, Vector<const T*>& connections)
	{
		if (startIndex < 0 || startIndex >= mNodes.Size())
			return;

		Reset();

		Vector<Node*> queue;
		queue.PushBack(mNodes[startIndex]);

		while (queue.Size() > 0)
		{
			Node* node = queue[0];
			queue.PopFront();

			if (!node->isVisited)
			{
				node->isVisited = true;
				connections.PushBack(node->data);

				for (std::size_t i = 0; i < node->edges.Size(); ++i)
				{
					Node* next = mNodes[node->edges[i]];
					if (!next->isVisited)
						queue.PushBack(next);
				}
			}
		}
	}


	bool GetPathDFS(int startIndex, int endIndex, Vector<const T*>& path)
	{
		if (startIndex < 0 || endIndex < 0 ||
			startIndex >= mNodes.Size() || endIndex >= mNodes.Size())
			return false;

		Reset();

		Vector<int> stack;
		stack.PushBack(startIndex);
		mNodes[startIndex]->isVisited = true;

		bool pathFound = false;

		while (stack.Size() > 0)
		{
			int current = stack[stack.Size() - 1];
			stack.PopBack();

			if (current == endIndex)
			{
				pathFound = true;
				break;
			}

			for (std::size_t i = 0; i < mNodes[current]->edges.Size(); ++i)
			{
				int next = mNodes[current]->edges[i];
				if (!mNodes[next]->isVisited)
				{
					mNodes[next]->isVisited = true;
					mNodes[next]->fromNode = current;
					stack.PushBack(next);
				}
			}
		}

		if (!pathFound)
			return false;

		for (int i = endIndex; i != -1; i = mNodes[i]->fromNode)
			path.PushBack(mNodes[i]->data);

		return true;
	}


	bool GetPathBFS(int startIndex, int endIndex, Vector<const T*>& path)
	{
		if (startIndex < 0 || endIndex < 0 ||
			startIndex >= mNodes.Size() || endIndex >= mNodes.Size())
			return false;

		Reset();

		Vector<int> queue;                     // ✅ queue stores INDICES
		queue.PushBack(startIndex);
		mNodes[startIndex]->isVisited = true;

		bool pathFound = false;

		while (queue.Size() > 0)
		{
			int current = queue[0];
			queue.PopFront();

			if (current == endIndex)
			{
				pathFound = true;
				break;
			}

			for (std::size_t i = 0; i < mNodes[current]->edges.Size(); ++i)
			{
				int next = mNodes[current]->edges[i];

				if (!mNodes[next]->isVisited)
				{
					mNodes[next]->isVisited = true;
					mNodes[next]->fromNode = current;   // ✅ store index
					queue.PushBack(next);               // ✅ push index
				}
			}
		}

		if (!pathFound)
			return false;

		// Reconstruct path (end → start)
		for (int i = endIndex; i != -1; i = mNodes[i]->fromNode)
		{
			path.PushBack(mNodes[i]->data);
		}

		return true;
	}

	//printing out all the nodes and their connections by the edges
	// printing out all the nodes and their connections by the edges
	void PrintGraph()
	{
		std::cout << "Printing Graph:\n";

		for (std::size_t i = 0; i < mNodes.Size(); ++i)
		{
			// Dereference to print the actual data, not the pointer
			std::cout << *mNodes[i]->data << ": ";

			for (std::size_t n = 0; n < mNodes[i]->edges.Size(); ++n)
			{
				int nodeIndex = mNodes[i]->edges[n];
				std::cout << *mNodes[nodeIndex]->data << " ";
			}

			std::cout << "\n";
		}
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
			mNodes[i]->fromNode = -1;
		}
	}

	Vector<Node*> mNodes;

};