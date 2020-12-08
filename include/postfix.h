#pragma once

#include "vector.h"
#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;

template <typename T>
class Queue : public Vector<T>
{
private:
	unsigned int front;
	unsigned int back;
	void resize(int n)
	{
		T* temp = new T[n];
		if (front < back)
		{
			for (size_t i = front; i <= back; i++)
				temp[i-front] = data[i];
		}
		else
		{
			for (size_t i = front; i < size; i++)
				temp[i-front] = data[i];
			for (size_t i = 0; i <= back; i++)
				temp[i+size-front] = data[i];
		}
		if (data)
			delete[]data;
		data = temp;
	}
public:
	Queue() : Vector() { front = 0; back = 0; }
	Queue(int n) : Vector(n) 
	{
		front = 0;
		back = n - 1; 
	}

	~Queue() {}

	void push(T elem) 
	{
		if (full())
			resize(size_t(2.0 * capacity));
		back++;
		if (back == capacity)
			back = 0;
		data[back] = elem;
		size++;
	}

	void pop() 
	{
		if (empty()) 
			throw "Smth wrong!";
		if (front == capacity)
			front = 0;
		else front++;
		size--;
	}

	bool empty() 
	{
		return size == 0;
	}

	bool full() 
	{
		return size == capacity;
	}
};
