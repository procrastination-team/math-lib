#include <iostream>
#include <string>
#include <vector>

void showUseCases() {
	std::cout << "1) to scalar multiply 2 vectors enter \"scalar row|column <number> row|column <number>\" like \"scalar row 3 row 4\".\n";
	std::cout << "2) to vector multiply select the vector that won't be used like \"vector column 2\"\n";
	std::cout << "3) To exit enter \"exit\"\n";
	std::cout << "> ";
}

std::vector<double> getVector(std::vector<std::vector<double>>& matrix, std::string pos, int num) {
	int n = matrix.size();
	std::vector<double> vect(n, 0);

	num %= n;

	if (pos == "row") {
		return matrix[num];
	}

	// if position equals "column"
	for (int i = 0; i < n; i++) {
		vect[i] = matrix[i][num];
	}

	return vect;
}

int multiplyScalar(std::vector<double> vect1, std::vector<double> vect2) {
	int res = 0;

	if (vect1.size() != vect2.size()) {
		return 0;
	}

	for (int i = 0; i < vect1.size(); i++) {
		res += vect1[i] * vect2[i];
	}

	return res;
}

std::vector<std::vector<double>> spliceMatrix(std::vector<std::vector<double>> matrix, std::string pos, int n) {
	if (pos == "row") {
		matrix.erase(matrix.begin() + n);
	}

	if (pos == "column") {
		for (int i = 0; i < matrix.size(); i++) {
			matrix[i].erase(matrix[i].begin() + n);
		}
	}

	return matrix;
}

std::string generateVectorName(int n) {
	std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
	std::string res = "";

	do {
		res += alphabet[n % alphabet.size()];
		n /= alphabet.size();
	} while (n > 0);

	std::reverse(res.begin(), res.end());

	return res;
}

double calcDeterminant(std::vector<std::vector<double>> matrix) {
	const int n = matrix.size();
	const double EPS = 1E-9;
	double det = 1;

	if (n != matrix[0].size()) {
		return 0;
	}

	for (int i = 0; i < n; ++i) {
		int k = i;

		for (int j = i + 1; j < n; ++j)
			if (abs(matrix[j][i]) > abs(matrix[k][i]))
				k = j;

		if (abs(matrix[k][i]) < EPS) {
			det = 0;
			break;
		}

		std::swap(matrix[i], matrix[k]);

		if (i != k)
			det = -det;

		det *= matrix[i][i];

		for (int j = i + 1; j < n; ++j)
			matrix[i][j] /= matrix[i][i];

		for (int j = 0; j < n; ++j)
			if (j != i && abs(matrix[j][i]) > EPS)
				for (int k = i + 1; k < n; ++k)
					matrix[j][k] -= matrix[i][k] * matrix[j][i];
	}

	return det;
}

std::string multiplyVectorwise(std::vector<std::vector<double>> matrix, std::string pos, int num) {
	int n = matrix.size();
	int determinant;
	std::string res = "";
	std::string vectorName;

	matrix = spliceMatrix(matrix, pos, num);

	if (pos == "row") {
		for (int i = 0; i < n; i++) {
			vectorName = generateVectorName(i);
			determinant = round(calcDeterminant(spliceMatrix(matrix, "column", i)));

			if (determinant == 0) {
				continue;
			}
			else if (determinant > 0 && (i + num) % 2 == 0 || determinant < 0 && (i + num) % 2 == 1) {
				if (i != 0) {
					res += "+ ";
				}
				res += std::to_string(abs(determinant)) + vectorName + " ";
			}
			else if (determinant > 0 && (i + num) % 2 == 1 || determinant < 0 && (i + num) % 2 == 0) {
				res += "-";

				if (i != 0) {
					res += " ";
				}

				res += std::to_string(abs(determinant)) + vectorName + " ";
			}
		}
	}

	if (pos == "column") {
		for (int i = 0; i < n; i++) {
			vectorName = generateVectorName(i);
			determinant = round(calcDeterminant(spliceMatrix(matrix, "row", i)));

			if (determinant == 0) {
				continue;
			}
			else if (determinant > 0 && (i + num) % 2 == 0 || determinant < 0 && (i + num) % 2 == 1) {
				if (i != 0) {
					res += "+ ";
				}
				res += std::to_string(abs(determinant)) + vectorName + " ";
			}
			else if (determinant > 0 && (i + num) % 2 == 1 || determinant < 0 && (i + num) % 2 == 0) {
				res += "-";

				if (i != 0) {
					res += " ";
				}

				res += std::to_string(abs(determinant)) + vectorName + " ";
			}
		}
	}

	return res;
}

int main() {
	unsigned int n = 0;
	std::string command;

	do {
		std::cout << "Set square matrix size: N\n";
		std::cin >> n;
	} while (n <= 0);

	std::cout << "Set matrix numbers NxN\n";

	std::vector<std::vector<double>> matrix(n, std::vector<double>(n));

	for (unsigned int i = 0; i < n; i++) {
		for (unsigned int j = 0; j < n; j++) {
			std::cin >> matrix[i][j];
		}
	}

	while (true) {
		showUseCases();

		std::cin >> command;

		if (command == "exit") {
			break;
		}

		if (command == "scalar") {
			std::string pos1, pos2;
			int num1, num2;

			std::cin >> pos1 >> num1 >> pos2 >> num2;

			num1--;
			num2--;

			std::vector<double> vect1 = getVector(matrix, pos1, num1);
			std::vector<double> vect2 = getVector(matrix, pos2, num2);

			std::cout << "Scalar multiplication: " << multiplyScalar(vect1, vect2) << "\n";
		}

		if (command == "vector") {
			std::string pos;
			int num;

			std::cin >> pos >> num;

			num--;

			std::cout << "Vector multiplication: " << multiplyVectorwise(matrix, pos, num) << "\n";
		}
	}

	return 0;
}