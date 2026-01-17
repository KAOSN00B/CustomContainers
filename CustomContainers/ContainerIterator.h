#pragma once

#include <algorithm>
#include <iterator>
#include <cstddef>

template<typename T>
class ContainerIterator
{
public:
	//define ids/names for stl use (std::sort, std::find etc) 
	//all these are required to use the stl functions
	using iterator_category = std::random_access_iterator_tag;
	using value_type = T;
	using difference_type = std::ptrdiff_t;
	using pointer = T*;
	using reference = T&;

public: // just used to seperate the top. doesn't do anything else

	//to create an iterator have to define it to the pointer
	ContainerIterator(T* ptr) : mPtr(ptr) {}

	T& operator*() const { return *mPtr; }
	T* operator->() const { return mPtr; }

	//++iter
	ContainerIterator& operator++() { ++mPtr; return *this; }
	//--iter
	ContainerIterator& operator--() { --mPtr; return *this; }
	//iter++
	ContainerIterator& operator++(int) { ContainerIterator temp = *this; ++(*this); return temp; }
	//iter--
	ContainerIterator& operator--(int) { ContainerIterator temp = *this; --(*this); return temp; }

	ContainerIterator operator+(difference_type n) const { return ContainerIterator(mPtr + n); }
	ContainerIterator operator-(difference_type n) const { return ContainerIterator(mPtr - n); }
	ContainerIterator& operator+=(difference_type n) { mPtr += n; return *this; }
	ContainerIterator& operator-=(difference_type n) { mPtr -= n; return *this; }

	difference_type operator-(const ContainerIterator& other) const { return mPtr - other.mPtr; }

	//compairson operators
	bool operator==(const ContainerIterator& other) const { return mPtr == other.mPtr; }
	bool operator!=(const ContainerIterator& other) const { return mPtr != other.mPtr; }
	bool operator>(const ContainerIterator& other) const { return mPtr > other.mPtr; }
	bool operator<(const ContainerIterator& other) const { return mPtr < other.mPtr; }
	bool operator>=(const ContainerIterator& other) const { return mPtr >= other.mPtr; }
	bool operator<=(const ContainerIterator& other) const { return mPtr <= other.mPtr; }

private:
	T* mPtr;

};