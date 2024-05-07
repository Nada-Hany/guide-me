#pragma once
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

class Hashing
{
private:
	const int MOD = 1e9 + 7;
	const short B1 = 37;
	const short B2 = 31;
	int multiply_under_mod(int a, int b, int c = 1, int d = 1, int e = 1);
	int add_under_mod(int a, int b, int c = 0, int d = 0, int e = 0);
	int fast_power(int a, int p);
	int mod_inverse(int a);

public:
	Hashing();
	pair<int, int> make_hash(const string& s);
};

