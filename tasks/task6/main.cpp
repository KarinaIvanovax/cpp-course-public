#include <cmath>
#include <string>
#include <functional>
#include <numeric>
#include <vector>
#include <thread>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <iomanip>


class Integral {
private:
	int a, b, n, tn;

public:
	Integral(int argc, char** argv) {
		if (argc != 5) {
			throw std::invalid_argument("Wrong number of arguments");
		}
		a = std::stoi(argv[1]);
		b = std::stoi(argv[2]);
		n = std::stoi(argv[3]);
		tn = std::stoi(argv[4]);
	}

	static double integralFunction(double x) {
		return sqrt(1 + exp(x));
	}


	double calculateIntegral() {
		double h = (b - a) / n;
		double s = 0.0;
#pragma omp parallel for num_threads(tn) reduction(+:s)
		for (int i = 0; i < n; i++) {
			double xi = a + i * h;
			s += integralFunction(xi) * h;
		}
		return s;
	}
};

int main(int argc, char** argv)
{
	try {
		auto i = Integral(argc, argv);
		std::cout << std::fixed << std::setprecision(4);
		std::cout << i.calculateIntegral() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what();
	}
	return 0;
}