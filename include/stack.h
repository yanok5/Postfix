#pragma once

#include <iostream>

const int MAX_STACK_SIZE = 1000;

template <typename T>
class Stack
{
protected:
	T *pStack;
	int Max;
public:
	int Size;
	Stack(int s = 10)
	{
		if (s < 0 || s > MAX_STACK_SIZE)
			throw "Smth wrong!";
		Size = 0;
		Max = s;
		pStack = new T[s];
	}

	Stack(const Stack &s)
	{
		Size = s.Size;
		Max = s.Max;
		pStack = new T[Max];
		for (int i = 0; i < Size; i++)
			pStack[i] = s.pStack[i];
	}

	~Stack() 
	{
		if (pStack)
		{
			delete[] pStack;
			pStack = nullptr;
		}
	}

	void Push(T elem)	// Добавить элемент в стек
	{
		if (Full())
		{
			Max = 2.0 * Max;
			T* temp = new T[Max];
			for (int i = 0; i < Size; i++)
				temp[i] = pStack[i];
			if (pStack)
				delete[]pStack;
			pStack = temp;
		}
		pStack[Size++] = elem;
	}

	T Pop()		// Удалить элемент из стека
	{
		auto ret = pStack[Size - 1];
		if (Empty())
			throw "Stack is empty";
		else
		{
			pStack[--Size] = 0;
		}

		return ret;
	}

	T Top()
	{
		if (Empty())
			throw "Stack is empty";
		return pStack[Size - 1];
	}

	bool Empty() { return Size == 0; }	// Проверка на пустоту стека
	bool Full() { return Max == Size; }	// Проверка на полноту стека
	
	Stack& operator=(const Stack &s)
	{
		Max = s.Max;
		Size = s.Size;
		if (pStack)
			delete[] pStack;
		pStack = new T[Max];

		for (int i = 0; i < Size; i++)
			pStack[i] = s.pStack[i];
		return *this;
	}

	bool operator==(const Stack &s) const
	{
		if ((Size != s.Size) || (Max != s.Max))
			return false;
		for (int i = 0; i < Max; i++)
		{
			if (pStack[i] != s.pStack[i])
			{
				return false;
			}
		}
		return true;
	}

	bool operator!=(const Stack &s) const { return !(s == *this); }
	T operator[](int pos)
	{
		if (pos < 0 || pos > Max)
			throw "Smth wrong";
		return pStack[pos];
	}
};
