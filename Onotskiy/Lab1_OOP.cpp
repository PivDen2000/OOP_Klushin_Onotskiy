//Piven Denys K-21
#define _USE_MATH_DEFINES
#include <iostream>;
#include <cmath>;
#include <iomanip>
using namespace std;

double segment[10] = { 0,0,0,0,0,0,0,0,0,0 };
const int e = 8, a = 3141, c = 2712, d = 73, m = 5153, m6 = 0, sgm = 1;

void info();
void MotherFunction(int num);
//Uniform Gistogramm for f1-f5
void gistoCounter(double u);
void gistoUniformOutput(int n);
//Normal Gistogramm for f6-f8
void gistoNormalOutput(int n);
//Other Gistogramm for f9-f10
void gistoOtherOutput(int n);
//f1
int f1(int &x);
//f2
int f2(int &x);
//f3
int f3(int &x, int x1, int x2);
//f4
int f4(int &x);
int gcd(int a, int b, int & x, int & y);
int inverseMod(int a, int m);
//f5
int f5(int &z);
//f6
int f6(int &x);
//f7
double f7(int &x);
//f8
double f8(int &x);
//f9
double f9(int &x);
//f10
double f10(int &x);

int main() {

	setlocale(LC_ALL, "Rus");
	info();
	int num;
	cin >> num;
	MotherFunction(num);

	/*int x = 1;
	double min = 100000, max = -100000, num = 0, n = 10000;
	for (int i = 0; i < n; i++) {
		cout << f10(x) << endl;
		num = f10(x);
		if (num < min)min = num;
		if (num > max)max = num;
	}
	cout << min << endl;
	cout << max << endl;*/

	system("pause");
	return 0;
}

void info() {
	cout << "Ìåòîäû ãåíåðàöèè ðàâíîìåðíîãî ðàñïðåäåëåíèÿ ÷èñåë:" << endl;
	cout << "	1 - Ëèíåéíûé êîíãðóýíòíûé ìåòîä." << endl;
	cout << "	2 - Êâàäðàòè÷íûé êîíãðóýíòíûé ìåòîä." << endl;
	cout << "	3 - ×èñëà Ôèáîíà÷÷è." << endl;
	cout << "	4 - Îáðàòíàÿ êîíãðóýíòíûé ïîñëåäîâàòåëüíîñòü." << endl;
	cout << "	5 - Ìåòîä îáúåäèíåíèÿ." << endl;
	cout << "Ìåòîäû ãåíåðàöèè íîðìàëüíîãî ðàñïðåäåëåíèÿ ÷èñåë:" << endl;
	cout << "	6 - Ïðàâèëî \"3 ñèãìà\"." << endl;
	cout << "	7 - Ìåòîä ïîëÿðíûõ êîîðäèíàò." << endl;
	cout << "	8 - Ìåòîä ñîîòíîøåíèé." << endl;
	cout << "Ìåòîäû ãåíåðàöèè äðóãèõ ðàñïðåäåëåíèé:" << endl;
	cout << "	9 - Ìåòîä ëîãàðèôìà äëÿ ãåíåðèðîâàíèÿ ïîêàçàòåëüíîãî ðàñïðåäåëåíèÿ." << endl;
	cout << "	10 - Ìåòîä Àðåíñà äëÿ ãåíåðàöèè ãàììà-ðàñïðåäåëåíèÿ ïîðÿäêà a>1." << endl;
	cout << "Ââåäèòå ÷èñëî îò 1 äî 10, äëÿ âûáîðà ñîîòâåòñòâóþùåãî ìåòîäà." << endl;
}

void MotherFunction(int num)
{
	//for all
	int x = 1;
	int n = 10000;
	double u = 0;

	//for fibonachi
	int x1 = 1, x2 = 1, t;

	//for f6-f8
	double min = 0, max = 0, div = 0, temp;

	switch (num)
	{
	default:
		break;
	case 1:
		for (int i = 0; i < n; i++) {
			f1(x);
			//cout << f1(x) << endl;
			u = (double)x / (double)m;
			gistoCounter(u);
		}
		gistoUniformOutput(n);
		break;
	case 2:
		for (int i = 0; i < n; i++) {
			f2(x);
			//cout << f2(x) << endl;
			u = (double)x / (double)m;
			gistoCounter(u);
		}
		gistoUniformOutput(n);
		break;
	case 3:
		for (int i = 0; i < n; i++) {
			f3(x, x1, x2);
			//cout << f3(x, x1, x2) << endl;
			u = (double)x / (double)m;
			t = x;
			x1 = x2;
			x2 = t;
			gistoCounter(u);
		}
		gistoUniformOutput(n);
		break;
	case 4:
		for (int i = 0; i < n; i++) {
			f4(x);
			//cout << f4(x) << endl;
			u = (double)x / (double)pow(2, e);
			gistoCounter(u);
		}
		gistoUniformOutput(n);
		break;
	case 5:
		for (int i = 0; i < n; i++) {
			f5(x);
			//cout << f5(x) << endl;
			u = (double)x / (double)m;
			gistoCounter(u);
		}
		gistoUniformOutput(n);
		break;
	case 6:
		for (int i = 0; i < n; i++) {
			f6(x);
			//cout << f6(x) << endl;
			min = 27957;
			max = 72746;
			div = max - min;
			u = ((double)x - min) /(div);
			gistoCounter(u);
		}
		gistoNormalOutput(n);
		break;
	case 7:
		for (int i = 0; i < n; i++) {
			temp = f7(x);
			//cout << f7(x) << endl;
			min = -1.88216;
			max = -0.0552937;
			div = max - min;
			u = ((temp)-min) / (div);
			gistoCounter(u);
		}
		gistoNormalOutput(n);
		break;
	case 8:
		for (int i = 0; i < n; i++) {
			temp = f8(x);
			//cout << f8(x) << endl;
			min = 0.0072172;
			max = 1.23109;
			div = max - min;
			u = ((temp)-min) / (div);
			gistoCounter(u);
		}
		gistoNormalOutput(n);
		break;
	case 9:
		for (int i = 0; i < n; i++) {
			temp = f9(x);
			//cout << f9(x) << endl;
			min = 0.0146661;
			max = 26.8522;
			div = max - min;
			u = ((temp)-min) / (div);
			gistoCounter(u);
		}
		gistoOtherOutput(n);
		break;
	case 10:
		for (int i = 0; i < n; i++) {
			temp = f10(x);
			//cout << f10(x) << endl;
			min = 0.00243866;
			max = 9.31047;
			div = max - min;
			u = ((temp)-min) / (div);
			gistoCounter(u);
		}
		gistoOtherOutput(n);
		break;
	}

	for (int k = 0; k < 10; k++) {
		segment[k] = 0;
	}
}

void gistoCounter(double u)
{
	if (0.0 < u&&u <= 0.1) { segment[0] += 1; }
	if (0.1 < u&&u <= 0.2) { segment[1] += 1; }
	if (0.2 < u&&u <= 0.3) { segment[2] += 1; }
	if (0.3 < u&&u <= 0.4) { segment[3] += 1; }
	if (0.4 < u&&u <= 0.5) { segment[4] += 1; }
	if (0.5 < u&&u <= 0.6) { segment[5] += 1; }
	if (0.6 < u&&u <= 0.7) { segment[6] += 1; }
	if (0.7 < u&&u <= 0.8) { segment[7] += 1; }
	if (0.8 < u&&u <= 0.9) { segment[8] += 1; }
	if (0.9 < u&&u <= 1.0) { segment[9] += 1; }
}

void gistoUniformOutput(int n)
{
	cout << "Èíòåðâàë	×àñòîòà" << endl;
	for (int i = 0; i < 10; i++) {
		cout << fixed << showpoint;
		cout << setprecision(1);
		cout << "[" << (double)i / 10 << "; " << (double)(i + 1) / 10 << "]	";
		cout << setprecision(2);
		cout << segment[i]/n << endl;
	}
	/*double sum = 0;
	for (int k = 0; k < 10; k++) {
		sum += segment[k];
	}
	cout << "Ñóììà:		" << sum/n << endl;*/
}

void gistoNormalOutput(int n)
{
	cout << "Èíòåðâàë	×àñòîòà" << endl;
	for (int i = 0; i < 10; i++) {
		cout << fixed << showpoint;
		cout << setprecision(1);
		cout << "[" << setw(4) << -3 + (double)i*0.6 << "; " << setw(4) << -3 + (double)(i + 1)*0.6 << "]	";
		cout << setprecision(2);
		cout << segment[i] / n << endl;
	}
	/*double sum = 0;
	for (int k = 0; k < 10; k++) {
		sum += segment[k];
	}
	cout << "Ñóììà:		" << sum / n << endl;*/
}

void gistoOtherOutput(int n)
{
	cout << "Èíòåðâàë	×àñòîòà" << endl;
	cout << fixed << showpoint;
	for (int i = 0; i < 10; i++) {
		cout << "[" << setw(2) << i * 10 << "; " << setw(3) << (i + 1) * 10 << "]	";
		cout << setprecision(2);
		cout << segment[i] / n << endl;
	}

	/*double sum = 0;
	for (int k = 0; k < 10; k++) {
		sum += segment[k];
	}
	cout << "Ñóììà:		" << sum / n << endl;*/
}

int f1(int & x)
{
	return x = (a * x + c) % m;
}

int f2(int & x)
{
	return x = (d*x*x + a * x + c) % m;
}

int f3(int &x, int x1, int x2)
{
	return x = (x1 + x2) % m;
}

int f4(int &x)
{
	int power = pow(2, e);
	return x = (a * inverseMod(x, e) + c) % power;
}

int gcd(int a, int b, int & x, int & y) {
	if (a == 0) {
		x = 0; y = 1;
		return b;
	}
	int x1, y1;
	int d = gcd(b%a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return d;
}

int inverseMod(int a, int e) {
	int x, y;
	int m = pow(2, e);
	int g = gcd(a, m, x, y);
	if (g != 1)
		return -1;
	else {
		x = (x % m + m) % m;
		return x;
	}
}

int f5(int & z)
{
	return abs(f1(z)-f2(z))%m;
}

int f6(int & x)
{
	int sum = 0;
	for (int i = 0; i < 20; i++) {
		sum += f1(x);
	}
	return x = m6 + (sum - 6)*sgm;
}

double f7(int & x)
{
	double v1, v2, s = 1, x1, x2;
	while (s >= 1) {
		v1 = (double)f1(x) / (double)m - 1;
		v2 = (double)f2(x) / (double)m - 1;
		s = pow(v1, 2) + pow(v2, 2);
	}
	x1 = v1 * sqrt(-2 * (log(s) / log(M_E)) / s);
	x2 = v2 * sqrt(-2 * (log(s) / log(M_E)) / s);
	return x1;
}

double f8(int & x)
{
	double u, v, xt;
	bool checker = 0;
	while (!checker) {
		u = (double)f1(x) / (double)m;
		v = (double)f2(x) / (double)m;

		xt = sqrt(8 / M_E)*(v - 1 / 2) / u;
		if (pow(xt, 2) <= 5 - 4 * pow(M_E, 1 / 4)*u) checker = true;
		if (pow(xt, 2) >= (4 * pow(M_E, -1.35)) / u + 1.4) checker = false;
		if (pow(xt, 2) <= -4 * (log(u) / log(M_E))) checker = true;
	}
	return xt;
}

double f9(int & x)
{
	double xt, u, miu = M_PI;
	
	u = (double)f1(x) / (double)m;

	if (u == 0) u = 0.135843;
	
	xt = -miu * log(u);

	return xt;
}

double f10(int & x)
{
	double xt = 0, u, v, y, a1 = 1;
	int x2 = 1;
	Again:
	while (xt <= 0) {
		u = (double)f1(x) / (double)m;
		y = tan(M_PI*u);
		xt = sqrt(2 * a1 - 1)*y + a1 - 1;
	}
	v = (double)f1(x) / (double)m;

	long double temper = (1 + pow(y, 2))*pow(M_E, (a1 - 1)*(log(xt / (a1 - 1))) - sqrt(2 * a1 - 1)*y);
	
	if (v > temper)
	{
		goto Again;
	}

	return xt;
}
