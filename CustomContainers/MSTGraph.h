#pragma once
#include "Vector.h"
#include <queue>
#include <vector>

template<typename T, typename W = int>
class MSTGraph
{
public:

	struct Edge
	{
		std::size_t fromIndex;
		std::size_t toIndex;
		W weight;

		bool operator<(const Edge& other) const
		{
			return weight < other.weight;
		}

		bool operator>(const Edge& other) const
		{
			return weight > other.weight;
		}
	};

	struct Node
	{
		const T* data = nullptr;
		bool isVisited = false;
		bool addedToProcess = false;
		W bestWeight = W();
		Vector<Edge> edges;
	};

public:

	MSTGraph()
	{
	}

	~MSTGraph()
	{
		Terminate();
	}

	void AddItem(const T* data)
	{
		Node* newNode = new Node();
		newNode->data = data;
		newNode->isVisited = false;
		mNodes.PushBack(newNode);
	}

	// assumes bidirectional edges
	void AddEdge(int a, int b, W weight, bool bothWays = true)
	{
		if (a < 0 || b < 0 || a >= mNodes.Size() || b >= mNodes.Size())
		{
			return;
		}

		Edge edgeA = { (std::size_t)a, (std::size_t)b, weight };
		mNodes[a]->edges.PushBack(edgeA);

		if (bothWays)
		{
			Edge edgeB = { (std::size_t)b, (std::size_t)a, weight };
			mNodes[b]->edges.PushBack(edgeB);
		}
	}

	void GenerateMST(int startNode)
	{
		// Prim's Algorithm
		Reset();

		std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> process;

		process.push({ (std::size_t)-1, (std::size_t)startNode, 0 });

		while (!process.empty())
		{
			Edge edge = process.top();
			process.pop();

			Node* node = mNodes[edge.toIndex];

			if (!node->isVisited)
			{
				node->isVisited = true;

				if (edge.fromIndex != (std::size_t)-1)
				{
					mMSTGraph.PushBack(edge);
				}

				for (std::size_t i = 0; i < node->edges.Size(); ++i)
				{
					const Edge& nextEdge = node->edges[i];
					Node* toNode = mNodes[nextEdge.toIndex];

					if (!toNode->isVisited &&
						(!toNode->addedToProcess || nextEdge.weight < toNode->bestWeight))
					{
						toNode->addedToProcess = true;
						toNode->bestWeight = nextEdge.weight;

						process.push(nextEdge);
					}
				}
			}
		}
	}

	const Vector<Edge>& GetMST() const
	{
		return mMSTGraph;
	}

	void Terminate()
	{
		for (std::size_t i = 0; i < mNodes.Size(); ++i)
		{
			delete mNodes[i];
			mNodes[i] = nullptr;
		}

		mNodes.Clear();
		mMSTGraph.Clear();
	}

private:

	void Reset()
	{
		for (std::size_t i = 0; i < mNodes.Size(); ++i)
		{
			mNodes[i]->isVisited = false;
			mNodes[i]->addedToProcess = false;
		}

		mMSTGraph.Clear();
	}

private:

	Vector<Node*> mNodes;
	Vector<Edge> mMSTGraph;

};