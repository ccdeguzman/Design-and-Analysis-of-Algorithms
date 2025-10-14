#ifndef PAPER1_H
#define PAPER1_H

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <chrono>
using namespace std;
using namespace chrono;

long long int euclid(long long int m, long long int n, long long int &divCount);
long long int decremental(long long int m, long long int n, long long int &divCount);
long long int modPow(long long base, long long int exp, long long int mod, long long &divCount);
bool isPrime(long long n);
long long int pollRho(long long int n, long long int &divCount);
vector<long long> pollRhoFactorize(long long n, long long &divCount);
long long gcdFactorization(long long m, long long n, long long &divCount);

#endif