//variant 78
//Piven Denys K-11

#include "functions.h"
#include <cmath>
#include <iostream>
using namespace std;

double accuracy(double x, double eps)
{
	double accuracy = 0;
	double temp = 0;
	double step = 0.000001;
	while (x < b) {
		temp = abs(S(x, eps) - f(x));

		if (temp > accuracy) {
			accuracy = temp;
		}

		x += step;
	}
	return accuracy;
}

int main() {

	cout.precision(10);
	cout << accuracy(-1, 0.0000000001) << endl;

	system("pause");
	return 0;
}