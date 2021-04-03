//variant 78
//Piven Denys K-11

#define _USE_MATH_DEFINES
#include <cmath>

double S(double x, double eps) noexcept
{
	double a = x * x * x / 6;
	double S = a;
	int n = 1;
	while (abs(a) >= eps)
	{
		a *= (-1)*n*(n + 1)* x * x / (2 * n + 2) / (2 * n + 3);
		S += a;
		n++;
	}
	return S;
}

double f(double x) noexcept
{
	return -2 * x + 2 * sqrt(4 + pow(x, 2))*asinh(x / 2);
}