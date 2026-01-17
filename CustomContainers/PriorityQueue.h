#pragma once

#include <iostream>
#include "Vector.h"

template<typename T>
class PriorityQueue
{
public:
	PriorityQueue() {}
	~PriorityQueue() {}

	bool Empty()
	{
		return mValues.Size() == 0;
	}

	const std::size_t Size()
	{
		return mValues.Size();
	}
	
	void Push(const T& value)
	{
		mValues.PushBack(value);
		HeapifyUp(Size() - 1);

		//sort
	}

	T Top() const
	{
		return mValues[0];
	}

	void Pop()
	{
		if (Empty()) { return; }
		
		mValues[0] = mValues[Size() - 1];
		mValues.Resize(Size() - 1);
		HeapifyDown(0);
		// sort again

	}

private:
	void Swap(T& value1, T& value2)
	{
		T temp = value1;
		value1 = value2;
		value2 = temp;
	}

	// maintain max-heap property for adding
	void HeapifyUp(int index)
	{
		int parent = (index - 1) / 2;
		while (index > 0 && mValues[index] > mValues[parent])
		{
			Swap(mValues[index], mValues[parent]);
			index = parent;
			parent = (index - 1) / 2;
		}
	}
	//for removing

	// add something to list. adds to vector swaps to the back and shifts it where it needs to go
	void HeapifyDown(int index)
	{
		int largest = index;
		int leftChild = 2 * index + 1;
		int rightChild = 2 * index + 2;

		if (leftChild < Size() && mValues[leftChild] > mValues[largest])
		{
			largest = leftChild;
		}

		if (rightChild < Size() && mValues[rightChild] > mValues[largest])
		{
			largest = rightChild;
		}

		if (largest != index)
		{
			Swap(mValues[index], mValues[largest]);
			HeapifyDown(largest);
		}
	}

	Vector<T> mValues;
};