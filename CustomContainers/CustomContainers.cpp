#include <iostream>
#include "Array.h"
#include "Vector.h"
#include "PriorityQueue.h"


int main()
{
	std::srand(static_cast<unsigned>(std::time(nullptr)));

	Array<int, 10> myInts;

	for (int i = 0; i < myInts.Size(); ++i)
	{
		myInts[i] = rand() % 100 ;
	}

	for (Array<int, 10>::Iterator iter = myInts.Begin(); iter != myInts.End(); ++iter)
	{
		std::cout << "Array Value: " << *iter << "\n";
	}

	std::sort(myInts.Begin(), myInts.End());
	std::cout << "\nSorted Values: \n";

	for (Array<int, 10>::Iterator iter = myInts.Begin(); iter != myInts.End(); ++iter)
	{
		std::cout << "Array Value: " << *iter << "\n";
	}

	PriorityQueue<int> priorityQueue;
	for (int i = 0; i < 20; ++i)
	{
		int value = rand() % 100;
		priorityQueue.Push(value);
		std::cout << value << " ";

	}
	std::cout << "\n\n";
	while (!priorityQueue.Empty())
	{
		std::cout << priorityQueue.Top() << " ";
		priorityQueue.Pop();
	}

	return 0;
}