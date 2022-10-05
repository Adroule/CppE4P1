#include <iostream>
#include <math.h>
#include<cstring>

bool isPrime(const long long& n) {
	if (n <= 1) return false;
	if (n <= 3) return true;

	int upperbound = std::sqrt(n);
	if (n % 2 == 0 || n % 3 == 0)
		return false;

	for (long long i = 5; i <= upperbound; i += 6) {
		if (n % i == 0 || n % (i + 2) == 0)
			return false;
	}
	return true;
}


int main(int argc, char* argv[]) {
	long long n;
	do {
		std::cin >> n;
		if (std::cin.good()) {
			if (isPrime(n)) {
				std::cout << n << " is a prime: True\n";
			}
			else {
				std::cout << n << " is a prime: False\n";
			}
		}
		else {
			std::cin.clear();
			break;
		}
	} while ((std::cin.peek() != '\n'));

}
