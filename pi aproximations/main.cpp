#include <iostream>

int iterations = 10000000;

long double wallis_product() {
	long double pi = 1.0;

	for (long double k = 1; k < iterations; k++) {
		pi *= (4 * k * k) / (4 * k * k - 1);
	}

	return pi * 2;
}

long double BBP_formula() {
	long double pi = 0.0;

	for (long double k = 0; k < iterations; k++) {
		pi += 1 / pow(16, k) * (4 / (8 * k + 1) - 2 / (8 * k + 4) - 1 / (8 * k + 5) - 1 / (8 * k + 6));
	}

	return pi;
}

long double Leibniz_formula() {
	long double pi = 0.0;

	for (long double k = 0; k < iterations; k++) {
		pi += pow(-1, k) / (2 * k + 1);
	}
	return pi * 4;
}

int main() {
	std::cout << "PI using dfferent methods" << std::endl;
	std::cout << "wallis product : " << wallis_product() << std::endl;
	std::cout << "BBP formula : " << BBP_formula() << std::endl;
	std::cout << "Leibniz formula : " << Leibniz_formula() << std::endl;

	return 0;
}