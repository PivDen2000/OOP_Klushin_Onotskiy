//variant 78
//Piven Denys K-11

#define _USE_MATH_DEFINES
#include <cmath>
using namespace std;

bool domain(double x)
{
	return (x > 15);
}

double f(double x)
{
	return sin(27. / 69) - 3 * M_PI + 46 * M_E * 14 / ((x - 3)*(x - 12)) + 7 * sin(x + 9) - 1 / sqrt(x - 15);
}

bool f(double x, double &res)
{
	if (domain(x))
	{
		res = f(x);
	}
	return domain(x);
}