#pragma once

#include <string>
#include <functional>
#include "Vector2.h"
#include "Vector.h"

namespace Globals //helps naming confilicts and can reuse this elsewhere
{
	std::size_t HashFunction(const std::string& str)
	{
		std::size_t hash = 0;

		for (std::size_t i = 0; i < str.size(); ++i)
		{
			hash = (~hash << 1) + (std::size_t)(str[i]);
		}
		return hash;
	}

	template<typename T>
	void Swap(T& a, T& b)
	{
		T temp = a;
		a = b;
		b = temp;
	}

	template<typename T>
	void BubbleSort(Vector<T>& values)
	{
		std::size_t size = values.Size();
		for (std::size_t i = 0; i < values.Size(); ++i)
		{
			for (std::size_t j = 0; j < size - i - 1; ++j)
			{
				if (values[j] > values[j + 1])
				{
					Swap(values[j], values[j + 1]);
				}
			}
		}
	}

	template<typename T, typename Compare>
	void BubbleSort(Vector<T>& values, Compare sortFunc)
	{
		std::size_t size = values.Size();

		for (std::size_t i = 0; i < size; ++i)
		{
			for (std::size_t j = 0; j < size - i - 1; ++j)
			{
				if (sortFunc(values[j + 1], values[j]))
				{
					Swap(values[j], values[j + 1]);
				}
			}
		}
	}



	template<typename T>
	void SelectionSort(Vector<T>& values)
	{
		int size = values.Size();
		for (std::size_t i = 0; i < size - 1; ++i)
		{
			std::size_t minIndex = i;
			for (std::size_t j = i + 1; j < size; ++j)
			{
				if (values[j] < values[minIndex])
				{
					minIndex = j;
				}

				if (i != minIndex)
				{
					Swap(values[i], values[minIndex]);
				}
			}
		}
	}

	template<typename T>
	void SelectionSort(Vector<T>& values, std::function<bool(const T&, const T&)> sortFunct)
	{
		std::size_t size = values.Size();
		for (std::size_t i = 0; i < size - 1; ++i)
		{
			std::size_t minIndex = i;
			for (std::size_t j = i + 1; j < size; ++j)
			{
				if (sortFunct(values[j], values[minIndex]))
				{
					minIndex = j;
				}

				if (i != minIndex)
				{
					Swap(values[j], values[minIndex]);
				}
			}
		}
	}

	// Template with type T and optional comparator (default: std::less on the iterator’s value_type) allowing customizable ordering behavior.
	template <typename T, typename Compare = std::less<typename std::iterator_traits<ContainerIterator<T>>::value_type>>
	void InsertionSort(ContainerIterator<T> begin, ContainerIterator<T> end, Compare comp = Compare())
	{
		if (begin == end)
		{
			return;
		}

		for (ContainerIterator<T> iter = begin + 1; iter != end; ++iter)
		{
			T key = *iter;
			ContainerIterator<T> j = iter;
			while (j > begin)
			{
				if (comp(key, *(j - 1)))
				{
					*j = *(j - 1);
					--j;
				}
				else
				{
					break;
				}
			}
			*j = key;
		}
	}

	// when we do globals only going to give access to that function
	//would need to explicitly call it
	namespace MergeSortHelpers
	{
		template<typename T, typename Compare>
		void Merge(ContainerIterator<T> left,ContainerIterator<T> mid,ContainerIterator<T> right,Compare comp)
		{
			Vector<T> temp;
			temp.Reserve(right - left);

			ContainerIterator<T> tempLeft = left;
			ContainerIterator<T> tempRight = mid;

			// Merge both halves while both have elements
			while (tempLeft != mid && tempRight != right)
			{
				if (comp(*tempLeft, *tempRight))
				{
					temp.PushBack(*tempLeft);
					++tempLeft;
				}
				else
				{
					temp.PushBack(*tempRight);
					++tempRight;
				}
			}

			// Copy remaining left half (if any)
			while (tempLeft != mid)
			{
				temp.PushBack(*tempLeft);
				++tempLeft;
			}

			// Copy remaining right half (if any)
			while (tempRight != right)
			{
				temp.PushBack(*tempRight);
				++tempRight;
			}

			// Copy merged result back into original range
			for (std::size_t i = 0; i < temp.Size(); ++i)
			{
				*(left + i) = temp[i];
			}
		}

		template<typename T, typename Compare>
		void MergeSortUtil(ContainerIterator<T> begin, ContainerIterator<T> end, std::size_t size, Compare comp)
		{
			if (size > 1)
			{
				std::size_t half = size / 2;
				ContainerIterator<T> mid = begin + half;
				// split the data

				MergeSortUtil(begin, mid, half, comp);
				MergeSortUtil(mid, end, size - half, comp);
				// merge the results
				Merge(begin, mid, end, comp);
			}
		}
	}
	template<typename T, typename Compare = std::less<typename std::iterator_traits<ContainerIterator<T>>::value_type>>
	void MergeSort(ContainerIterator<T> begin, ContainerIterator<T> end, Compare comp = Compare())
	{
		std::size_t size = end - begin;
		MergeSortHelpers::MergeSortUtil(begin, end, size, comp);
	}

	namespace QuickSortHelpers
	{
		template<typename T, typename Compare>
		ContainerIterator<T> Partition(ContainerIterator<T> begin, ContainerIterator<T> end, Compare comp)
		{
			ContainerIterator<T> pivot = end - 1;
			ContainerIterator<T> i = begin;
			for (ContainerIterator<T> j = begin; j != pivot; ++j)
			{
				Swap(*i, *pivot);
				++i;
			}
			Swap(*i, *pivot);
			return i;
		}
	}
	template<typename T, typename Compare = std::less<typename std::iterator_traits<ContainerIterator<T>>::value_type>>
	void QuickSort(ContainerIterator<T> begin, ContainerIterator<T> end, Compare comp = Compare())
	{
		if (begin < end && (end - begin) < 1)
		{
			ContainerIterator<T> p = QuickSortHelpers::Partition(begin, end, comp);
			QuickSort(begin, p, comp);
			QuickSort(p + 1, end, comp);
		}
	}

	//can only sort lowest to highest
	template<typename T,typename Compare = std::less<typename std::iterator_traits<ContainerIterator<T>>::value_type>>
	void BucketSort(ContainerIterator<T> begin,ContainerIterator<T> end, Compare comp = Compare())
	{
		if (begin == end) return;

		// Find max value
		ContainerIterator<T> maxValue = begin;
		for (ContainerIterator<T> iter = begin + 1; iter != end; ++iter)
		{
			if (comp(*maxValue, *iter))
			{
				maxValue = iter;
			}
		}

		std::size_t size = end - begin;
		if (*maxValue == 0) return; // prevent divide by zero

		Vector<Vector<T>> buckets;
		buckets.Resize(size);

		// Distribute elements into buckets
		for (ContainerIterator<T> iter = begin; iter != end; ++iter)
		{
			std::size_t bucketIndex =
				((size - 1) * (*iter)) / (*maxValue);

			buckets[bucketIndex].PushBack(*iter);
		}

		// Sort each bucket
		for (std::size_t i = 0; i < size; ++i)
		{
			InsertionSort(buckets[i].Begin(),
				buckets[i].End(),
				comp);
		}

		// Combine buckets back into original range
		ContainerIterator<T> output = begin;

		for (std::size_t i = 0; i < size; ++i)
		{
			for (std::size_t j = 0; j < buckets[i].Size(); ++j)
			{
				*output = buckets[i][j];
				++output;
			}
		}
	}

	namespace HeapSortHelpers
	{
		template<typename T, typename Compare>
		void Heapify(ContainerIterator<T> begin, ContainerIterator<T> root, std::size_t count, Compare comp)
		{
			std::size_t rootIndex = root - begin;
			std::size_t largestIndex = rootIndex;

			std::size_t leftIndex = 2 * rootIndex + 1;
			std::size_t rightIndex = 2 * rootIndex + 2;

			if (leftIndex < count &&
				comp(*(begin + largestIndex), *(begin + leftIndex)))
			{
				largestIndex = leftIndex;
			}

			if (rightIndex < count && comp(*(begin + largestIndex), *(begin + rightIndex)))
			{
				largestIndex = rightIndex;
			}

			if (largestIndex != rootIndex)
			{
				Swap(*(begin + rootIndex), *(begin + largestIndex));

				Heapify(begin, begin + largestIndex, count, comp);
			}
		}
	}

	template<typename T, typename Compare = std::less<typename std::iterator_traits<ContainerIterator<T>>::value_type>
	>
	void HeapSort(ContainerIterator<T> begin, ContainerIterator<T> end, Compare comp = Compare())
	{
		std::size_t count = end - begin;
		if (count <= 1)
			return;

		// Build heap
		for (std::size_t i = count / 2; i > 0; --i)
		{
			HeapSortHelpers::Heapify(begin, begin + (i - 1), count, comp);
		}

		// Extract elements
		for (std::size_t i = count - 1; i > 0; --i)
		{
			Swap(*begin, *(begin + i));

			HeapSortHelpers::Heapify(begin, begin, i, comp);
		}
	}

	namespace IntroSortHelpers
	{
		template<typename T, typename Compare>
		void IntroSortUtil(ContainerIterator<T> begin, ContainerIterator<T> end, int depthLimit, Compare comp)
		{
			std::size_t count = end - begin;

			// Small range → insertion sort
			if (count < 16)
			{
				InsertionSort(begin, end, comp);
				return;
			}

			// Depth limit reached → heapsort
			if (depthLimit <= 0)
			{
				HeapSort(begin, end, comp);
				return;
			}

			// Quicksort partition
			ContainerIterator<T> pivot = QuickSortHelpers::Partition(begin, end, comp);

			// Recurse on left side
			IntroSortUtil(begin, pivot, depthLimit - 1, comp);

			// Recurse on right side
			IntroSortUtil(pivot + 1, end, depthLimit - 1, comp);
		}
	}

	template<typename T,typename Compare = std::less<typename std::iterator_traits<ContainerIterator<T>>::value_type>>
	void IntroSort(ContainerIterator<T> begin, ContainerIterator<T> end, Compare comp = Compare())
	{
		std::size_t count = end - begin;
		if (count <= 1)
			return;

		int depthLimit = 2 * static_cast<int>(std::log2(count));

		IntroSortHelpers::IntroSortUtil(begin, end, depthLimit, comp);
	}

}
