#pragma once
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

class Hashing
{
private:
	const long long MOD = 1e9 + 7;
	const short B1 = 37;
	const short B2 = 31;
	long long multiply_under_mod(long long a, long long b);
	long long add_under_mod(long long a, long long b);
	long long fast_power(long long a, long long p);
	long long mod_inverse(long long a);

public:
	Hashing();
	size_t make_hash(const string& s);
};

