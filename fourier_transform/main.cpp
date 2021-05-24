#include <iostream>
#include <cmath>
#include <vector>
#include "../common/complex/complex.hpp"

using namespace std;

const double PI = 3.141592653589793238463;

void fft(vector<common::Complex<double>>& a) {
	int n = a.size();

	if (n == 1) {
		return;
	}

	vector<common::Complex<double>> a0(n / 2), a1(n / 2);

	for (int i = 0, j = 0; i < n; i += 2, j++) {
		a0[j] = a[i];
		a1[j] = a[i + 1];
	}

	fft(a0);
	fft(a1);

	double ang = 2 * PI / n;
	common::Complex<double> w(1), wn(cos(ang), sin(ang));

	for (int i = 0; i < n / 2; i++) {
		a[i] = a0[i] + w * a1[i];
		a[i + n / 2] = a0[i] - w * a1[i];
		w = w * wn;
	}
}

int nearestPowerOfTwo(double num) {
	return pow(2, ceil(log(num) / log(2)));
}

int main() {
	int n;
	string read_line;

	cout << "Enter the number of coefficients in a polynomial:\n> ";
	cin >> n;
	cout << "Enter the coefficients of the polynomial zj = aj+bji:\nz0\nz1\n...\nzn\n> ";

	vector<common::Complex<double>> a(nearestPowerOfTwo(n), common::Complex<double>(0));

	for (int i = 0; i < n; i++) {
		cin >> read_line;

		a[i] = common::parse_complex<double>(read_line);

		if (i < n - 1) {
			cout << "> ";
		}
	}

	fft(a);

	cout << "(";

	for (int i = 0; i < a.size(); i++) {
		cout << a[i];

		if (i < a.size() - 1) {
			cout << ", ";
		}
	}

	cout << ")";

	return 0;
}