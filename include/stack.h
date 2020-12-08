#pragma once

#include <iostream>

const int MAX_SIZE = 1000;

template <class T>
class Vector
{
protected:
	T* data;
	size_t size;
	size_t capacity;
public:
	Vector()
	{
		data = nullptr;
		size = 0;
		capacity = 0;
	}

	~Vector()
	{
		if (data)
		{
			delete[] data;
			data = nullptr;
		}
	}

	Vector(int n)
	{
		if (n < 0 || n > MAX_SIZE)
			throw "Smth wrong";
		else
		{
			size = n;
			capacity = n;
			data = new T[n];
			for (int i = 0; i < n; i++)
				data[i] = 0;
		}
	}

	Vector(int n, T* A)
	{
		size = n;
		capacity = n;
		data = new T[size];
		for (size_t i = 0; i < size; i++)
			data[i] = A[i];
	}

	Vector(const Vector& v)
	{
		size = v.size;
		capacity = v.capacity;
		T* data = new T[capacity];
		for (size_t i = 0; i < size; i++)
			data[i] = v.data[i];
		for (size_t i = size; i < capacity; i++)
			data[i] = 0;
	}

	void push_back(T elem)
	{
		if (size == capacity)
		{
			capacity = 2.0 * capacity;
			T* temp = new T[capacity];
			for (int i = 0; i < size; i++)
				temp[i] = data[i];
			if (data)
				delete[]data;
			data = temp;
		}
		data[size++] = elem;
	}

	void pop_back()
	{
		data[--size] = 0;
	}

	void push_front(T elem)
	{
		insert(elem, 0);
	}

	void pop_front()
	{
		erase(0);
	}

	void resize(int n)
	{
		T* temp = new T[n];
		if (size > n)
		{
			for (size_t i = 0; i < n; i++)
				temp[i] = data[i];
			size = n;
		}
		else
		{
			for (size_t i = 0; i < size; i++)
				temp[i] = data[i];
			for (size_t i = size; i < n; i++)
				temp[i] = 0;
		}
		if (data)
			delete[]data;
		data = temp;
	}

	void insert(T elem, int index)
	{
		T* temp = new T[size + 1];
		for (int i = 0; i < index; i++)
			temp[i] = data[i];
		temp[index] = elem;
		for (i = index; i < size; i++)
			temp[i + 1] = data[i];
		if (data)
			delete[] data;
		data = temp;
	}

	void erase(int index)
	{
		if (index > size - 1)
			return;
		T* temp = new T[capacity];
		for (int i = 0; i < index; i++)
			temp[i] = data[i];
		for (int i = index + 1; i < size; i++)
			temp[i - 1] = data[i];
		if (data)
			delete[]data;
		data = temp;
		size--;
	}

	T& operator[](int index)
	{
		return this->data[index];
	}
	T operator[](int index)const
	{
		return this->data[index];
	}
};
