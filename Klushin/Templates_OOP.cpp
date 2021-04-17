//Piven K-21 and Kushnir K-21
#include <cstdio>
#include <iostream>
#include <cmath>
#define DEPTH 8

const long double PI = 3.14159265358979323f;

// FACTORIAL
using namespace std;
template <int N> struct fact
{
	static const long long value;
};
template <int N> const long long fact<N>::value  = N * fact<N - 1>::value;
template <> struct fact<1>
{
	static const long long value = 1L;
};

//power

template <class X, int N> struct power
{
	static const long double value;
};

template <class X, int N> const long double power<X, N>::value
= X::value * power<X, N - 1>::value;

template <class X>
struct power<X, 0>
{
	static const long double value;
};

template <class X> const long double power<X, 0>::value = 1.0f;

// Exponent
//
template <class X, int N> struct Exp
{
	static const long double value;
};

template<class X, int N>
const long double Exp<X , N>::value = power<X, N>::value / fact<N>::value + Exp<X, N - 1>::value;

template<class X>
struct Exp<X,0>
{
	static const long double value;
};

template<class X>
const long double Exp<X, 0>::value =1 ;

//exp repeat
template <class X, int N, int M> struct ExpRepeat
{
	static const long double value;
};

template<class X, int N, int M>
const long double ExpRepeat<X, N, M>::value = Exp<ExpRepeat<X , N , M-1> , N >::value;
template<class X, int N>
struct ExpRepeat<X, N, 1>
{
	static const long double value;
};
template<class X, int N>
const long double ExpRepeat<X, N, 1>::value = Exp<X, N>::value;

 //SIMPLIFY RADI

// SIMPLIFY RADIAN TO INTERVAL [-2π, 2π]

template <class X> struct SimplifyRad
{
	static const long double value;
};

template <class X> const long double SimplifyRad<X>::value =

X::value - (2 * PI * (double)(int)(X::value / (2 * PI))); // float modulo?

// COSINE

template <class X, int N> struct cosine
{
	static const long double value;
};

template <class X, int N> const long double cosine<X, N>::value =

(((N % 2 == 0 ? 1 : -1) * power<SimplifyRad<X>, 2 * N>::value) / ((long double)
	fact<2 * N>::value)) + cosine<X, N - 1>::value;

template <class X> struct cosine<X, 0>
{
	static const long double value;
};

template <class X> const long double cosine<X, 0>::value = 1.0f;

// sineE

template <class X, int N> struct sine
{
	static const long double value;
};

template <class X, int N> const long double sine<X, N>::value =

(((N % 2 == 0 ? -1 : 1) * power<SimplifyRad<X>, 2 * N - 1>::value) / ((long double)
	fact<2 * N - 1>::value)) + sine<X, N - 1>::value;

template <class X> struct sine<X, 0>
{
	static const long double value;
};

template <class X> const long double sine<X, 0>::value = 0.0f;

//ln pow
template <class X, int N> struct powerln
{
	static const long double value;
};

template <class X, int N> const long double powerln<X, N>::value
= (X::value - 1) * powerln<X, N - 1>::value;

template <class X> struct powerln<X, 0>
{
	static const long double value;
};

template <class X> const long double powerln<X, 0>::value = 1.0f;

// ln

template <class X, int N> struct ln
{
	static const long double value;
};

template <class X, int N> const long double ln<X, N>::value =

((N % 2 == 0 ? -1 : 1) * powerln<X, N>::value) / (long double)fact<N>::value + ln<X, N - 1>::value;

template <class X> struct ln<X, 1>
{
	static const long double value;
};

template <class X> const long double ln<X, 1>::value = X::value - 1;

//ln repeat
template <class X, int N, int M> struct LnRepeat
{
	static const long double value;
};

template<class X, int N, int M>
const long double LnRepeat<X, N, M>::value = ln<LnRepeat<X, N, M - 1>, N >::value;
template<class X, int N>
struct LnRepeat<X, N, 1>
{
	static const long double value;
};
template<class X, int N>
const long double LnRepeat<X, N, 1>::value = ln<X, N>::value;

// sinRepeat

template <class X, int N, int M> struct SinRepeat
{
	static const long double value;
};

template<class X, int N, int M>
const long double SinRepeat<X, N, M>::value = sine<SinRepeat<X, N, M - 1>, N >::value;
template<class X, int N>
struct SinRepeat<X, N, 1>
{
	static const long double value;
};
template<class X, int N>
const long double SinRepeat<X, N, 1>::value = sine<X, N>::value;

// cosRepeat

template <class X, int N, int M> struct CosRepeat
{
	static const long double value;
};

template<class X, int N, int M>
const long double CosRepeat<X, N, M>::value = cosine<CosRepeat<X, N, M - 1>, N >::value;
template<class X, int N>
struct CosRepeat<X, N, 1>
{
	static const long double value;
};
template<class X, int N>
const long double CosRepeat<X, N, 1>::value = cosine<X, N>::value;

struct var
{
	static const long double value;
};
const long double var::value = 0.5;

struct expo
{
	static const long double value;
};
const long double expo::value = 2.7;

struct order
{
	static const long double value;
};
const long double order::value = 8;

struct repeat
{
	static const long double value;
};
const long double repeat::value = 2;

int main(int argc, char *argv[])
{
	cout << SinRepeat<CosRepeat<LnRepeat<ExpRepeat<var, 8, 2>,8,2>,8,3>,8,4>::value << endl;
	system("pause");
}