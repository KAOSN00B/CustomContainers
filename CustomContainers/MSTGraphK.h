#pragma once
#include "Vector.h"
#include "Globals.h"

class DisJointSetUnion
{
public:

	DisJointSetUnion(int numNodes)
	{
		mParent.Resize(numNodes);
		mRank.Resize(numNodes, 0);

		for (int i = 0; i < numNodes; ++i)
		{
			mParent[i] = i;
		}
	}

	int FindParentIndex(int nodeIndex)
	{
		if (mParent[nodeIndex] != nodeIndex)
		{
			mParent[nodeIndex] = FindParentIndex(mParent[nodeIndex]);
		}

		return mParent[nodeIndex];
	}

	bool UnionEdges(int from, int to)
	{
		int rootFrom = FindParentIndex(from);
		int rootTo = FindParentIndex(to);

		if (rootFrom == rootTo)
		{
			return false;
		}

		if (mRank[rootFrom] < mRank[rootTo])
		{
			mParent[rootFrom] = rootTo;
		}
		else if (mRank[rootFrom] > mRank[rootTo])
		{
			mParent[rootTo] = rootFrom;
		}
		else
		{
			mParent[rootTo] = rootFrom;
			++mRank[rootFrom];
		}

		return true;
	}

private:
	Vector<int> mParent;
	Vector<int> mRank;
};

template<typename T>
class MSTGraphK
{
public:

	struct Edge
	{
		int fromNode = -1;
		int toNode = -1;
		T weight = T();
	};

public:

	void Clear()
	{
		mEdges.Clear();
		mMSTEdges.Clear();
	}

	void AddEdge(int a, int b, T weight)
	{
		Edge newEdge = { a, b, weight };
		mEdges.PushBack(newEdge);
	}

	void GenerateMST()
	{
		int numNodes = mEdges.Size();

		mMSTEdges.Clear();

		DisJointSetUnion dsu(numNodes);

		Globals::IntroSort(mEdges.Begin(), mEdges.End(),
			[](const Edge& a, const Edge& b)
			{
				return a.weight < b.weight;
			});

		for (std::size_t i = 0; i < mEdges.Size(); ++i)
		{
			Edge& edge = mEdges[i];

			if (dsu.UnionEdges(edge.fromNode, edge.toNode))
			{
				mMSTEdges.PushBack(edge);

				if (mMSTEdges.Size() == numNodes - 1)
				{
					break;
				}
			}
		}
	}

	const Vector<Edge>& GetMST() const
	{
		return mMSTEdges;
	}

private:
	Vector<Edge> mEdges;
	Vector<Edge> mMSTEdges;
};