//Piven Denys K-21
#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <assert.h>
#include <fstream>
#include <vector>
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
	bool operator<(const LongDynamics& other) const;
	LongDynamics operator+(const LongDynamics& other) const;
	LongDynamics operator-(const LongDynamics& other) const;
	LongDynamics operator*(const LongDynamics& other) const;
	LongDynamics operator*(const int& other) const;
	LongDynamics operator/(const int& other) const;
	void padRight(size_t num);
	void padLeft(size_t num);
	void output();
	void removeLeadingZeros();
	LongDynamics KaratsubaMult(const LongDynamics & a, const LongDynamics & b);
	
	string num = "0";
	int index = 0;
	bool sign = 0; //0 = +, 1 = -;
};

void equalizeLengths(string& first, string& second);
LongDynamics Power(LongDynamics& main, LongDynamics& power);

int main() {

	system("pause");
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

bool LongDynamics::operator<(const LongDynamics & other) const
{
	if (sign < other.sign) {
		return false;
	}
	if (sign > other.sign) {
		return true;
	}

	return num < other.num;
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

LongDynamics Power(LongDynamics & main, LongDynamics & power)
{
	LongDynamics result = main;
	LongDynamics One("1");
	
	while (power.num > "1") {
		result = result * stoi(main.num);
		power = power - One;
	}

	return result;
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

void LongDynamics::padRight(size_t num) {
	this->num += std::string(num, '0');
}

void LongDynamics::padLeft(size_t num) {
	this->num.insert(0, num, '0');
}

LongDynamics LongDynamics::KaratsubaMult(const LongDynamics & a, const LongDynamics & b)
{
	LongDynamics A = a;
	LongDynamics B = b;

	equalizeLengths(A.num,B.num);

	assert(A.size() == B.size());
	size_t sz = A.size();

	// Base case 
	if (sz <= 1) {
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

	this->num = result.num;
	return result;
}