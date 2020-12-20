#pragma once

#include <string>
#include "math.h"
#include "stdlib.h"
#include "stack.h"

using namespace std;

class Postfix
{
	string infix;
	string postfix;
	bool Operator(char op)
	{
		if (op == '+' || op == '-' || op == '*' || op == '/')
			return true;
		else return false;
	}

	int Priority(char a, char b)	// 0 - одинаковы, 1 - a приоритетнее, 2 - b приоритетнее
	{
		if ((a == '*' || a == '/') && (b == '*' || b == '/'))
			return 0;
		if ((a == '+' || a == '-') && (b == '+' || b == '-'))
			return 0;
		if ((a == '*' || a == '/') && (b == '+' || b == '-'))
			return 1;
		if ((a == '+' || a == '-') && (b == '*' || b == '/'))
			return 2;
		throw "No such operation";
	}

public:
	Postfix(string str = "a+b")
	{
		infix = str;
	}
	Postfix(Postfix &p)
	{
		infix = p.infix;
		postfix = p.postfix;
	}
	~Postfix() {}
	string GetInfix() { return infix; }
	string GetPostfix() { return postfix; }
	bool CheckOperators()
	{
		if (Operator(infix[0]) && (infix[0] != '-') || Operator(infix.back()))
			return false;
		for (int i = 0; i < infix.size() - 1; i++)
		{
			if (Operator(infix[i]) && Operator(infix[i + 1]))
				return false;
		}
		return true;
	}

	bool CheckInfix()
	{
		CheckOperators();
		int status = 0;
		int brakets = 0;
		for (int i = 0; i < infix.size(); i++)
		{
			switch (status)
			{
			case 0:
				if (infix[i] == '\0')
					status = 2;
				else if (infix[i] == '(')
				{
					brakets++;
					status = 0;
				}
				else if (infix[i] >= '0' && infix[i] <= '9')
				{
					status = 1;
					int dot = 0;
					while (((infix[i + 1] >= '0') && (infix[i + 1] <= '9')) || (infix[i + 1] == '.'))
					{
						i++;
						if (infix[i] == '.')
							dot++;
					}
					if (dot > 1)
						return false;
				}
				else return false;
				break;
			case 1:
				if (infix[i] == '\0')
					status = 2;
				if (infix[i] == ')')
				{
					brakets--;
					if (brakets >= 0)
						status = 1;
					if (brakets < 0)
						return false;
				}
				if (Operator(i))
					status = 0;
				if ((!Operator(i)) && infix[i] != ')' && infix[i] != '\0')
					return false;
				break;
			case 2:
				if (brakets == 0)
					return true;
				if (brakets != 0)
					return false;
				break;
			}
		}
	}

	string Postfix::ToPostfix()
	{
		postfix.clear();
		Stack<char> opers(infix.size());
		for (int i = 0; i < infix.size(); i++)
		{
			if (!Operator(infix[i]) && infix[i] != '-' && infix[i] != '(' && infix[i] != ')')
			{
				while (!Operator(infix[i]) && i != infix.size() && infix[i] != ')')
				{
					postfix += infix[i];
					i++;
				}
				postfix += ' ';
				i--;
			}
			else if (opers.Empty())
					opers.Push(infix[i]);
			else if (infix[i] == '(')
				opers.Push(infix[i]);
			else if (opers.Top() == '(')
				opers.Push(infix[i]);
			else if (infix[i] == ')')
			{
				char curr_elem = opers.Pop();
				while (curr_elem != '(')
				{
					postfix += curr_elem;
					postfix += ' ';
					curr_elem = opers.Pop();
				}
			}
			else if (Priority(infix[i], opers.Top()) >= 1)
			{
				opers.Push(infix[i]);
			}
			else
			{
				while ((opers.Top() != '('))
				{
					if (Priority(infix[i], opers.Top()) == 1)
						break;
					postfix += opers.Pop();
					postfix += ' ';
					if (opers.Empty())
						break;
				}
				opers.Push(infix[i]);
			}
		}
		while (!opers.Empty())
		{
			char curr_oper = opers.Pop();
			if (curr_oper != '(')
			{
				postfix += curr_oper;
				postfix += ' ';
			}
		}

		postfix.pop_back();

		return postfix;
	}

	double Postfix::Calculate()
	{
		ToPostfix();
		Stack<double> nums(infix.size());
		double result = 0.0;
		for (int i = 0; i < postfix.size(); i++)
		{
			if (Operator(postfix[i]))
			{
				switch (postfix[i])
				{
					case '+':
					{
						double p = nums.Pop();
						result = nums.Pop() + p;
						nums.Push(result);
						break;
					}
					case '-':
					{
						double p = nums.Pop();
						result = nums.Pop() - p;
						nums.Push(result);
						break;
					}
					case '*':
					{
						double p = nums.Pop();
						result = nums.Pop() * p;
						nums.Push(result);
						break;
					}
					case '/':
					{
						double p = nums.Pop();
						if (p == 0.0) 
							throw string("Division is impossible");
						result = nums.Pop() / p;
						nums.Push(result);
						break;
					}
					default:
						throw "Invalid operation";
				}
			}
			else
			{
				if (postfix[i] != ' ')
				{
					string str;
					while (postfix[i] != ' ')
					{
						str += postfix[i];
						i++;
					}
					double number = stod(str);
					nums.Push(number);
				}
			}
		}
		return nums.Top();
	}
};
