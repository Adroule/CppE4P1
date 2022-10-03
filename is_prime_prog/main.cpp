#include <iostream>
#include <math.h>
#include<cstring>

bool isPrime(const int& n){

	int upperbound=std::sqrt(n)+1;
	for (int i=2; i< upperbound; i++){
		if (n%i==0){
			return false;
		}
	}
	return true;
}


int main(int argc, char *argv[]){
	int n;
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