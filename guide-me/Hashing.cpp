#include "Hashing.h"
#include <utility>
#include <iostream>
#include <string>
using namespace std;

long long Hashing::add_under_mod(long long a, long long b) {
	return (a + b) % MOD;
}

long long Hashing::multiply_under_mod(long long a, long long b) {
	return (1LL * a * b) % MOD;
}

long long Hashing::fast_power(long long num, long long power) {
	if (power == 1) return num;
	if (power == 0) return 1;
	long long half = fast_power(num, power / 2);

	if (power & 1) half = multiply_under_mod(half, num);
	return half;
}

long long Hashing::mod_inverse(long long a) {
	return fast_power(a, MOD - 2);
}

Hashing::Hashing() {

}

size_t Hashing::make_hash(const string& s) {
	pair<long long, long long> temp;
	for (long long i = 0; i < s.size(); i++) {
		long long character_number = s[i] - 'a' + 1;
		pair<long long, long long> hash_of_the_character;
		hash_of_the_character.first = multiply_under_mod(character_number, fast_power(B1, i));
		hash_of_the_character.second = multiply_under_mod(character_number, fast_power(B2, i));
		temp.first = add_under_mod(temp.first, hash_of_the_character.first);
		temp.second = add_under_mod(temp.second, hash_of_the_character.second);
	}
	return temp.first ^ (temp.second << 31);
}