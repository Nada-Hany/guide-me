#include "Hashing.h"
#include <utility>
#include <iostream>
#include <string>
using namespace std;

int Hashing::add_under_mod(int a, int b, int c = 0, int d = 0, int e = 0) {
	return (a + b + c + d + e) % MOD;
}

int Hashing::multiply_under_mod(int a, int b, int c = 1, int d = 1, int e = 1) {
	return (1LL * a * b * c * d * e) % MOD;
}

int Hashing::fast_power(int num, int power) {
	if (power == 1) return num;
	int half = fast_power(num, power / 2);

	if (power & 1) half = multiply_under_mod(half, num);
	return half;
}

int Hashing::mod_inverse(int a) {
	return fast_power(a, MOD - 2);
}

Hashing::Hashing() {

}

pair<int, int> Hashing::make_hash(const string& s) {
	pair<int, int> temp;
	for (int i = 0; i < s.size(); i++) {
		int character_number = s[i] - 'a' + 1;
		pair<int, int> hash_of_the_character;
		hash_of_the_character.first = multiply_under_mod(character_number, fast_power(B1, i));
		hash_of_the_character.second = multiply_under_mod(character_number, fast_power(B2, i));
		temp.first = add_under_mod(temp.first, hash_of_the_character.first);
		temp.second = add_under_mod(temp.second, hash_of_the_character.second);
	}
	return temp;
}