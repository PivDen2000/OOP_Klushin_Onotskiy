//variant 78
//Piven Denys K-11

#include <iostream>
#include "copyright.h"
#include "functions.h"
using namespace std;

int main()
{
	copyright();
	cout << "This program calculates the value of exercise 78" << endl;

	double x;
	cout << "Enter the value of 'x':" << endl;
	cin >> x;

	double result;
	cout << "***** do calculations ... ";
	bool trueX = f(x, result);
	cout << "done" << endl;
	cout << "for x = " << x << endl;
	if (trueX)

	{
		cout << "result = " << result << endl;
	}
	else
	{
		cout << "result = undefined " << endl;
	}

	system("pause");
	return 0;
}