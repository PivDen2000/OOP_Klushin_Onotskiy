//Piven Denys K-21
#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <assert.h>
using namespace std;

class LongDynamics {
public:
	LongDynamics();
	LongDynamics(const string& input);
	LongDynamics(const string& input, const bool& sign);
	LongDynamics operator=(const LongDynamics & other);
	LongDynamics(const LongDynamics& other);
	~LongDynamics();
	size_t size() const;
	bool operator!=(const LongDynamics& other) const;
	bool operator==(const LongDynamics& other) const;
	bool operator>(const LongDynamics& other) const;
	LongDynamics operator%(const LongDynamics& other) const;
	LongDynamics operator+(const LongDynamics& other) const;
	LongDynamics operator-(const LongDynamics& other) const;
	LongDynamics operator*(const LongDynamics& other) const;
	LongDynamics operator*(const int& other) const;
	LongDynamics operator/(const int& other) const;
	void padRight(size_t num);
	void padLeft(size_t num);
	void output();
	void removeLeadingZeros();
	LongDynamics BinToTen(const LongDynamics& a);

	//M1
	LongDynamics KaratsubaMult(const LongDynamics& first, const LongDynamics& second);
	//M2
	LongDynamics ToomCookMult(const LongDynamics& first, const LongDynamics& second);
	//M3
	LongDynamics SchonhageMult(const LongDynamics& first, const LongDynamics& second);
	//M4
	LongDynamics StrassenMult(const LongDynamics& first, const LongDynamics& second);
	//M5
	LongDynamics CookInverse(const LongDynamics& x);
	//M6 
	LongDynamics CookDivide(const LongDynamics& first, const LongDynamics& second);
private:
	string num = "0";
	bool sign = 0; //0 = +, 1 = -;
};

//M7
bool LemanPrime(const int& n);
//M8
bool RabinMillerPrime(const int& n);
//M9
bool SolovayStrassenPrime(const int& n, const int& t);
//M10
bool AgravalPrime(const int& n);
LongDynamics factorial(LongDynamics n);
int Binom(int n, int k);
bool FermatPrime(const int& n, const int& t);

void info();
void CharDigitIndex(char a = '0');
void equalizeLengths(string& first, string& second);
int gcd(int a, int b, int & x, int & y);
int inverseMod(int a, int m);
int powmod(int base, int exp, int modulo);

int main() {

	setlocale(LC_ALL, "Rus");
	
	//LongDynamics a("1234567890",0);
	//LongDynamics b("1234567876543", 0);
	//LongDynamics multK;
	//LongDynamics multT;

	//multK = multK.KaratsubaMult(a, b);
	//multT = multT.ToomCookMult(a, b);

	//a.output();
	//b.output();
	//multK.output();
	//multT.output();
	
	int a = 1111111;
	int b = 1111117;
	int t = 100;

	cout << LemanPrime(a) << endl;
	cout << RabinMillerPrime(a) << endl;
	cout << AgravalPrime(a) << endl;
	cout << SolovayStrassenPrime(a,t) << endl;
	cout << LemanPrime(b) << endl;
	cout << RabinMillerPrime(b) << endl;
	cout << AgravalPrime(b) << endl;
	cout << SolovayStrassenPrime(b, t) << endl;



	system("pause>>void");
	return 0;
}

LongDynamics::LongDynamics()
{
}

LongDynamics::LongDynamics(const string & input)
{
	for (size_t i = 0; i < input.size(); i++) {
		if (input[i] < '0' || input[i] > '9') {
				throw out_of_range("Incorrect value");
		}
	}
	num = input;
}

LongDynamics::LongDynamics(const string & input, const bool & sign)
{
	LongDynamics temp(input);
	num = temp.num;
	this->sign = sign;
}

LongDynamics LongDynamics::operator=(const LongDynamics & other)
{
	num = other.num;
	sign = other.sign;
	return *this;
}

LongDynamics::LongDynamics(const LongDynamics & other)
{
	this->num = other.num;
	this->sign = other.sign;
}

LongDynamics::~LongDynamics()
{
}

size_t LongDynamics::size() const
{
	return num.size();
}

bool LongDynamics::operator!=(const LongDynamics & other) const
{
	LongDynamics first = *this, second = other;
	if (sign != other.sign) return 1;

	first.removeLeadingZeros();
	second.removeLeadingZeros();

	if (first.num != second.num) return 1;

	return 0;
}

bool LongDynamics::operator==(const LongDynamics & other) const
{
	return !(*this != other);
}

bool LongDynamics::operator>(const LongDynamics & other) const
{
	LongDynamics first = *this, second(other);

	if (sign > other.sign) return 0;
	if (sign < other.sign) return 1;

	first.removeLeadingZeros();
	second.removeLeadingZeros();

	equalizeLengths(first.num, second.num);

	if (first.num > second.num) return 1;
	return 0;
}

LongDynamics LongDynamics::operator%(const LongDynamics & other) const
{
	LongDynamics result = *this, two("2");

	while (*this > other) {
		if (other == two) {
			result.num = this->num[this->size()];
			break;
		}
		result = result - other;
	}
	
	return result;
}

LongDynamics LongDynamics::operator+(const LongDynamics & other) const
{
	LongDynamics result;
	string sum;
	string first = num;
	string second = other.num;
	result.sign = sign;

	equalizeLengths(first, second);

	if (sign == other.sign) {

		int pos = first.size() - 1;
		int mind = 0;
		while (pos >= 0) {
			int digit = (first[pos] - '0') + (second[pos] - '0') + mind;
			mind = 0;
			if (digit > 9) {
				digit = digit % 10;
				mind = 1;
			}
			sum.push_back(digit + '0');
			--pos;
		}
		if (mind) sum.push_back('1');
	
		result.sign = sign;
	}
	else {
		if (first < second) {
			string temp = first;
			first = second;
			second = temp;
			result.sign = other.sign;
		}

		int pos = first.size() - 1;

		while (pos >= 0) {
			int digit;
			if (first[pos] >= second[pos]) {
				digit = (first[pos] - '0') - (second[pos] - '0');
			}
			else {
				int next_pos = pos - 1;
				while (true) {
					if (first[next_pos] > 0) {
						break;
					}
					--next_pos;
				}
				--first[next_pos];

				next_pos++;
				while (next_pos != pos) {
					assert(first[next_pos] == 0);
					first[next_pos] = '9';
					next_pos++;
				}
				digit = 10 + (first[pos] - '0') - (second[pos] - '0');
			}
			sum.push_back(digit + '0');
			--pos;
		}


	}

	reverse(sum.begin(), sum.end());

	result.num = sum;
	
	result.removeLeadingZeros();
	
	return result;
}

LongDynamics LongDynamics::operator-(const LongDynamics & other) const
{
	LongDynamics result;
	string diff;
	string first = num;
	string second = other.num;
	result.sign = sign;

	equalizeLengths(first, second);

	if (sign != other.sign) {

		int pos = first.size() - 1;
		int mind = 0;
		while (pos >= 0) {
			int digit = (first[pos] - '0') + (second[pos] - '0') + mind;
			mind = 0;
			if (digit > 9) {
				digit = digit % 10;
				mind = 1;
			}
			diff.push_back(digit + '0');
			--pos;
		}
		if (mind) diff.push_back('1');

		result.sign = sign;
	}
	else {
		if (first < second) {
			string temp = first;
			first = second;
			second = temp;
			sign ? result.sign = 0 : result.sign = 1;
		}
		else {
			sign ? result.sign = 1 : result.sign = 0;
		}

		int pos = first.size() - 1;

		while (pos >= 0) {
			int digit;
			if (first[pos] >= second[pos]) {
				digit = (first[pos] - '0') - (second[pos] - '0');
			}
			else {
				int next_pos = pos - 1;
				while (true) {
					if (first[next_pos] > 0) {
						break;
					}
					--next_pos;
				}
				--first[next_pos];

				next_pos++;
				while (next_pos != pos) {
					assert(first[next_pos] == 0);
					first[next_pos] = '9';
					next_pos++;
				}
				digit = 10 + (first[pos] - '0') - (second[pos] - '0');
			}
			diff.push_back(digit + '0');
			--pos;
		}
	}

	reverse(diff.begin(), diff.end());

	result.num = diff;

	result.removeLeadingZeros();

	return result;
}

LongDynamics LongDynamics::operator*(const LongDynamics & other) const
{
	LongDynamics result;

	if (num == "" || other.num == "") {
		return result;
	}

	((other.sign) != sign) ? result.sign = 1 : result.sign = 0;

	result.num = to_string(stoi(num)*stoi(other.num));
	return result;
}

LongDynamics LongDynamics::operator*(const int & other) const
{
	LongDynamics result;
	LongDynamics addit = this->num;

	for (int i = 0; i < abs(other); i++) {
		result = result + addit;
	}
	
	((other < 0) != this->sign) ? result.sign = 1 : result.sign = 0;

	return result;
}

LongDynamics LongDynamics::operator/(const int & other) const
{
	LongDynamics result;

	(sign == (other < 0)) ? result.sign = 0 : result.sign = 1;

	int pos = 0;
	int decreaser;
	int subtrahend;

	decreaser = (this->num[pos] - '0');

	while (pos < num.size()) {
		result.num.push_back(decreaser / other + '0');
		subtrahend = other * (decreaser / other);
		pos++;
		decreaser = (decreaser - subtrahend) * 10 + (this->num[pos] - '0');
	}

	result.removeLeadingZeros();

	return result;
}

void equalizeLengths(string & first, string & second)
{
	if (first.size() != second.size()) {
		reverse(first.begin(), first.end());
		reverse(second.begin(), second.end());
		if (first.size() < second.size()) {
			first += string(second.size() - first.size(), '0');
		}
		else if (first.size() > second.size()) {
			second += string(first.size() - second.size(), '0');
		}
		reverse(first.begin(), first.end());
		reverse(second.begin(), second.end());
	}
}

void info()
{
	cout << "Умножение неотрецательных целых:" << endl;
	cout << "	1) Метод Картацубы" << endl;
	cout << "	2) Метод Тоома-Кука" << endl;
	cout << "	3) Метод Шенхаге" << endl;
	cout << "	4) Метод Штрассена" << endl;
	cout << "Нахождение обратной величены:" << endl;
	cout << "	5) Алгоритм Кука 1" << endl;
	cout << "Деление целых:" << endl;
	cout << "	6) Алгоритм Кука 2" << endl;
	cout << "Проверка простоты числа:" << endl;
	cout << "	7) Метод Лемана" << endl;
	cout << "	8) Метод Рабина-Миллера" << endl;
	cout << "	9) Метод Соловая-Штрассена" << endl;
	cout << "	10) Агравала (АКС)" << endl;
}

void CharDigitIndex(char a)
{
	cout << a << '	' << (int)a << endl;
	cout << '0' << '	' << (int)'0' << endl;
	cout << '1' << '	' << (int)'1' << endl;
	cout << '2' << '	' << (int)'2' << endl;
	cout << '3' << '	' << (int)'3' << endl;
	cout << '4' << '	' << (int)'4' << endl;
	cout << '5' << '	' << (int)'5' << endl;
	cout << '6' << '	' << (int)'6' << endl;
	cout << '7' << '	' << (int)'7' << endl;
	cout << '8' << '	' << (int)'8' << endl;
	cout << '9' << '	' << (int)'9' << endl;
}

void LongDynamics::output()
{
	this->removeLeadingZeros();
	string minus = '-' + num;
	(sign) ? cout << minus << endl : cout << num << endl;
}

void LongDynamics::removeLeadingZeros()
{
	num.erase(0, num.find_first_not_of('0'));
}

LongDynamics LongDynamics::BinToTen(const LongDynamics & a)
{
	LongDynamics A = a;
	LongDynamics result;
	LongDynamics temp;

	int sz = A.size();

	for (int i = 0; i < sz; i++) {
		temp.num = to_string((A.num[sz - i] - '0')*pow(2, i));
		result = result + temp;
	}

	return result;
}

int powmod(int base, int exp, int modulo)
{
	int res = 1;

	while (exp > 0)
	{
		if (exp % 2 == 0)
		{
			exp = exp / 2;
			base = base * base % modulo;
		}
		else
		{
			exp = exp - 1;
			res = 1ll* res * base % modulo;
		}
	}

	return res % modulo;
}

LongDynamics LongDynamics::KaratsubaMult(const LongDynamics & a, const LongDynamics & b)
{
	LongDynamics A = a;
	LongDynamics B = b;

	equalizeLengths(A.num,B.num);

	assert(A.size() == B.size());
	size_t sz = A.size();

	// Base case 
	if (sz == 1) {
		return A * B;
	}

	int m = sz / 2;
	LongDynamics A0 = A.num.substr(m, sz - m);
	LongDynamics A1 = A.num.substr(0, m);
	LongDynamics B0 = B.num.substr(m, sz - m);
	LongDynamics B1 = B.num.substr(0, m);

	LongDynamics A0B0 = KaratsubaMult(A0, B0);
	LongDynamics A1B1 = KaratsubaMult(A1, B1);

	LongDynamics A0_plus_A1 = A0 + A1;
	LongDynamics B0_plus_B1 = B0 + B1;
	LongDynamics MULT = KaratsubaMult(A0_plus_A1, B0_plus_B1);

	LongDynamics A0B1_plus_A1B0 = MULT - A0B0 - A1B1;

	A0B1_plus_A1B0.padRight(sz - m);
	A1B1.padRight(2 * (sz - m));

	LongDynamics result = A0B0 + A0B1_plus_A1B0 + A1B1;
	result.removeLeadingZeros();
	(a.sign != b.sign) ? result.sign = 1 : result.sign = 0;
	
	this->num = result.num;
	return result;
}

LongDynamics LongDynamics::ToomCookMult(const LongDynamics & a, const LongDynamics & b)
{
	LongDynamics A = a;
	LongDynamics B = b;
	LongDynamics result;

	equalizeLengths(A.num, B.num);

	assert(A.size() == B.size());
	size_t sz = A.size();

	// Base case 
	if (sz <= 2) {
		return A * B;
	}

	if (sz % 3 == 1) {
		A.padLeft(2);
		B.padLeft(2);
	}
	if (sz % 3 == 2) {
		A.padLeft(1);
		B.padLeft(1);
	}
	sz = A.size();

	long int m = sz / 3;

	LongDynamics A0 = A.num.substr(sz - m, m);
	LongDynamics A1 = A.num.substr(sz - 2 * m, m);
	LongDynamics A2 = A.num.substr(0, sz - 2 * m);

	LongDynamics B0 = B.num.substr(sz - m, m);
	LongDynamics B1 = B.num.substr(sz - 2 * m, m);
	LongDynamics B2 = B.num.substr(0, sz - 2 * m);

	LongDynamics first[3] = { A2,A1,A0 };
	LongDynamics second[3] = { B2,B1,B0 };

	LongDynamics PoliOne[5] = {};
	LongDynamics PoliTwo[5] = {};

	for (int i = -2; i <= 2; i++) {
		PoliOne[i + 2] = A2 * i*i + A1 * i + A0;
		PoliTwo[i + 2] = B2 * i*i + B1 * i + B0;
	}

	LongDynamics PoliMult[5] = {};

	for (size_t i = 0; i < 5; i++) {
		PoliMult[i] = ToomCookMult(PoliOne[i], PoliTwo[i]);
	}

	LongDynamics Newton[5] = { PoliMult[0],PoliMult[1] ,PoliMult[2] ,PoliMult[3] ,PoliMult[4] };

	for (size_t k = 1; k < 5; k++) {
		for (size_t i = 0; i < 4; i++) {
			LongDynamics diff = PoliMult[i + 1] - PoliMult[i];
			PoliMult[i] = diff / k;
		}
		Newton[k] = PoliMult[0];
	}

	LongDynamics NewtonTemp[6] = { Newton[0],Newton[1],Newton[2],Newton[3],Newton[4] };

	for (int i = 0; i < 4; i++) {
		NewtonTemp[5] = NewtonTemp[4 - i];
		NewtonTemp[4 - i].padRight(m);
		NewtonTemp[4 - i] = Newton[3 - i] + NewtonTemp[4 - i] + NewtonTemp[5] * (i - 1);
		NewtonTemp[3 - i] = NewtonTemp[4 - i];
	}

	result = NewtonTemp[0];
	(a.sign != b.sign) ? result.sign = 1 : result.sign = 0;
	result.removeLeadingZeros();

	this->num = result.num;
	return result;
}

//LongDynamics LongDynamics::SchonhageMult(const LongDynamics & a, const LongDynamics & b)
//{
//	LongDynamics A = a;
//	LongDynamics B = b;
//	LongDynamics result;
//	
//	equalizeLengths(A.num, B.num);
//
//	assert(A.size() == B.size());
//	size_t sz = A.size();
//
//	int pk, qk;
//	
//	//find qk
//	for (int k = 0; k < sz; k++) {
//		qk = (pow(3, k) + 1) / 2;
//		pk = 18 * qk + 8;
//		if (pk >= sz) break;
//	}
//
//	A.padLeft(pk - sz);
//	B.padLeft(pk - sz);
//
//	int m1, m2, m3, m4, m5, m6;
//	m1 = pow(2, 6 * qk - 1);
//	m2 = pow(2, 6 * qk + 1);
//	m3 = pow(2, 6 * qk + 2);
//	m4 = pow(2, 6 * qk + 3);
//	m5 = pow(2, 6 * qk + 5);
//	m6 = pow(2, 6 * qk + 7);
//
//	A = BinToTen(a);
//	B = BinToTen(b);
//
//	equalizeLengths(A.num, B.num);
//
//	int u1, u2, u3, u4, u5, u6;
//
//}

void LongDynamics::padRight(size_t num) {
	this->num += std::string(num, '0');
}

void LongDynamics::padLeft(size_t num) {
	this->num.insert(0, num, '0');
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

int inverseMod(int a, int m) {
	int x, y;
	int g = gcd(a, m, x, y);
	if (g != 1) {
		return -1;
	}
	else {
		x = (x % m + m) % m;
		return x;
	}
}

int jacob_char( __int64 a, __int64 b)
{
	int x, y;
	if (gcd(a, b, x, y) != 1)
		return 0;
	else
	{
		int r = 1;
		if (a < 0)
		{
			a = -a;
			if (b % 4 == 3)
				r = -r;
		}
		do
		{
			int t = 0;
			while (a % 2 == 0)
			{
				t += 1;
				a /= 2;
			}
			if (t % 2 == 1 && (b % 8 == 3 || b % 8 == 5))
				r = -r;
			if (a % 4 == 3 && b % 4 == 3)
				r = -r;
			unsigned __int64 c = a;
			a = b % c;
			b = c;
		} while (a != 0);
		return r;
	}
}

bool LemanPrime(const int & n)
{
	int t = 1000000;
	int a, temp;
	double prozent = 1;

	bool result = 1;
	for (int i = 0; i < t; i++) {
		//1
		a = rand() % n;
		//2
		temp = powmod(a, (n - 1) / 2, n);
		//3
		if (temp != 1 && temp != -1) result = 0;
		//4
		if (temp == 1 || temp == -1) prozent /= 2;
	}

	//cout << prozent << endl;

	return result;
}

bool RabinMillerPrime(const int& n)
{
	int i, temp;
	bool not_prime = 0;
	unsigned int s = 0, q, m, j, k, p[58] = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,
		131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271 }, pq[58];

	// (1) проверка n на то, является ли оно степенью числа
	for (i = 3; i <= sqrt(n); i += 2)
	{
		temp = n;
		unsigned int power = 0;
		while (temp / i > 0 && temp%i == 0)
		{
			temp /= i;
			power++;
		}
		if (temp == 1 && power > 1)
		{
			not_prime = 1;
			break;
		}
	}

	if (!not_prime)
	{
		for (m = 0; m < 58 - 1; m++)
			if (p[m] <= pow(n, 0.133) && pow(n, 0.133) <= p[m + 1])
			{
				m++;
				break;
			}
		// находим s и q, где n-1 = q*2^s, q - нечетное
		temp = n - 1;
		while (temp / 2 > 0 && temp % 2 == 0)
		{
			temp /= 2;
			s++;
		}
		q = (n - 1) / pow(2, s);
		// i=1, (4)

		// (3) если i<=m, то i=i+1
		for (i = 1; i <= m; i++)
		{
			// (4) не очень понятна запись p[i] | n
			// полагаю, что означает она делимость n на p[i], т.е. является ли p[i] делителем n
			if (n % p[i - 1] == 0)
			{
				not_prime = 1;
				break;
			}
			// вычисляем p[i]^q mod n, p[i]^(q*2) mod n, ..., p[i]^(q*2^s) mod n, обозначим их pq[i]
			for (j = 0; j <= s; j++)
				pq[j] = powmod(p[i - 1], q*pow(2, j), n);
			// (5) проверяем условие pq[i]^(q*2^s) != 1, если да, то число составное
			if (pq[s] != 1)
			{
				not_prime = 1;
				break;
			}
			// (6) проверяем условие pq[i]^q == 1, если да, то идем на (3)
			if (pq[0] == 1)
				continue;
				temp = 0;
			for (j = 0; j <= s; j++)
				if (pq[j] != 1 && pq[j] > temp)
				{
					temp = pq[j];
					k = j;  // запоминаем индекс j (в переменной k)
				}
			// (7) если pq[j] (j=k, см. чуть выше), то (3)
			if (pq[k] == n - 1)
				continue;

			// (8)
			not_prime = 1;
		}
		// (3) случай i>m
		if (!not_prime)
			return 1;
	}
	else {
		return 0;
	}
}

bool SolovayStrassenPrime(const int& n, const int & t)
{
	int a, k, j;
	//1
	for (int i = 0; i < t; i++) {
		//1.1
		a = 2 + rand() % n;
		//1.2
		k = powmod(a, (n - 1) / 2, n);
		//1.3
		if (k != 1 && k != n - 1) return 0;
		//1.4
		j = jacob_char(a, n);
		//1.5
		if (k != j) return 0;
	}
	//2
	return 1;
}

bool AgravalPrime(const int & n)
{
	//(x-1)^n-(x^n-1)
	for (int a = 1; a < sqrt(n); a++) {
		for (int b = 2; b < (double)log(n) / log(2); b++) {
			if (n == pow(a, b)) return 0;
		}
	}
}

LongDynamics factorial(LongDynamics n)
{
	LongDynamics zero("0"), one("1");

	if (n == zero) return one;

	return zero.KaratsubaMult(n, factorial(n - one));
}

bool FermatPrime(const int & n, const int & t)
{
	int a, k;
	for (int i = 1; i < t; i++) {
		//1.1
		a = 2 + rand() % n;
		//1.2
		k = powmod(a, n - 1, n);
		//1.3
		if (k != 1) return 0;
	}
	return 1;
}