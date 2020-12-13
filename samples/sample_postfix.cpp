#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
	string expression;
	while (true)
	{
		cout << "Enter an arithmetic expression: ";
		cin >> expression;
		Postfix postfix(expression);
		if (!postfix.CheckInfix())
		{
			cout << "Invalid expression" << endl << endl;
			break;
		}
		cout << "Infix form: " << postfix.GetInfix() << endl;
		postfix.ToPostfix();
		cout << "Postfix form: " << postfix.GetPostfix() << endl;
		try 
		{
			cout << "Result: " << postfix.Calculate() << endl << endl;
		}
		catch (string ex)
		{
			cout << "Catch an exeption: " << ex << endl;
		}
		break;
	}
	return 0;
}
