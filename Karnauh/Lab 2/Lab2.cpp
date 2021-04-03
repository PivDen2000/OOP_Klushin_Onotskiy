//variant 78
//Piven Denys K-11

#include <iostream>
#include <string>
#include "copyright.h"
#include "functions.h"
using namespace std;

//calculates max difference between S(x) and f(x)
double accuracy() {
	double eps = 0.0000001;
	double x = a;
	double accuracy = 0;
	double temp = 0;
	double step = 0.000001;
	while (x < b) {
		temp = abs(S(x, eps) - f(x));

		if (abs(temp) > abs(accuracy)) {
			accuracy = temp;
		}

		x += step;
	}
	return accuracy;
}

//displays the invitation, provides a valid value and controls the input errors
double input(const string &message) {
	double q;
	cout << message << endl;
	cin >> q;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		throw runtime_error("Error: input invalid number");
	}
	return q;
}

int main()
{
	copyright();
	cout << "This program calculates the value of exercise 78" << endl;
	
	cout.precision(10);
	cout << fixed << "***** accuracy = " << 0.0000000173<< endl;

	double x;
	double eps;
	
	try
	{
		x = input("Enter the value of 'x' from: [" + to_string(a) + "; " + to_string(b) + "]:");
		
		if (x > b || x < a) {
			throw domain_error ("Error: value of 'x' out of domain");
		}

		eps = input("Enter the value of 'eps' in (0; +inf):");

		if (eps <= 0) {
			throw domain_error("Error: value of 'eps' out of domain");
		}

		double result;
		cout << "***** do calculations ... ";

		result = S(x, eps);

		cout << "done" << endl;

		cout.precision(4);
		cout << "for x = " << x << endl;

		cout.precision(10);
		cout << "result = " << result << endl;
	}
	catch (runtime_error &e)
	{
		cout << e.what() << endl;
	}
	catch (domain_error &e)
	{
		cout << e.what() << endl;
	}
	catch (...) 
	{
		cout << "Something goes wrong" << endl;
	}

	system("pause");
	return 0;
}