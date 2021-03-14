// Determinant C++
#include <iostream>
#include <cstdio>

using namespace std;

void Display(double *, int);

double CalculateDeterminant(double *&, int);

//double Determinant(double *&, int);

double DeterminantIterative(double *&, int);

double ResolveRows(double **, int, int, int);

void Display(double **, int);

int main() {
    int N;
    bool isFileInp;
    cout
            << "Если вы хотите использовать файловый ввод/вывод - введите 1, если хотите использовать консольный - введите 0:\n";
    cin >> isFileInp;
    if (isFileInp) {
        freopen("output.txt", "w", stdout);
        freopen("input.txt", "r", stdin);
    }
    if (not isFileInp) {
        cout << "Введте размер матрицы (N):\n";
    }
    cin >> N;
    double *S = new double[N * N];
    double det;
    for (int i = 0; i < N * N; i++) {
        if (not isFileInp) {
            cout << "Введте элемент матрицы (" << i % N << ", " << i / N << "):\n";
        }
        cin >> S[i];
    }

    det = CalculateDeterminant(S, N);
    cout << "Determinant = " << det << "\n";

    return 0;
}

void Display(double *arr, const int N) {
    for (int i = 0; i < N * N; i++)
        cout << arr[i] << ((i + 1) % N ? "\t" : "\n");
}

double CalculateDeterminant(double *&S, const int N) {
    double rez;
    if (N < 1) {
        cout << "Размер матрицы должен быть больше нуля\n";
        return 0.0;
    } else if (N == 1)
        rez = *S;
    else if (N == 2)
        rez = S[0] * S[3] - S[1] * S[2];
    else if (N == 3)
        rez = S[0] * S[4] * S[8] + S[1] * S[5] * S[6] + S[2] * S[3] * S[7] -
              S[2] * S[4] * S[6] - S[1] * S[3] * S[8] - S[0] * S[5] * S[7];
    else
        rez = DeterminantIterative(S, N);
    return rez;
}

double DeterminantIterative(double *&S, const int N) {
    //Киреев, Пантелеев
    //Вержбицкий
    double **M = new double *[N];
    for (int i = 0; i < N; i++)
        M[i] = new double[N];

    for (int i = 0; i < N * N; i++)
        M[i / N][i % N] = S[i];
    cout << "\n\n  Начльная матрица\n\n";
    Display(M, N);
    double determinant = 1;
    for (int i = 0; i < N - 1; i++)
        for (int j = i + 1; j < N; j++)
            while (M[j][i] != 0) {
                determinant *= ResolveRows(M, N, i, j);

                if (determinant == 0)
                    return 0;
            }
    for (int i = 0; i < N; i++)
        determinant *= M[i][i];
    for (int i = 0; i < N; i++)
        delete[] M[i];
    delete[] M;
    delete[] S;
    return determinant;
}

double ResolveRows(double **M, const int N, int f, int s) {
    printf("\n\n  f[%d][%d] = %f,\ts[%d][%d] = %f \n",
           f, f, M[f][f], s, f, M[s][f]);

    int sign = 1;
    int NonZeroRowIndex = s;
    while (M[f][f] == 0) {
        sign *= -1;
        printf("  Поменять строку [%d] со строкой [%d] поменять знак\n", f, s);
        double *tmp = M[NonZeroRowIndex];
        M[NonZeroRowIndex] = M[f];
        M[f] = tmp;
        NonZeroRowIndex++;
        if (M[f][f] != 0)
            return sign;
        if (NonZeroRowIndex == N && M[f][f] == 0)
            return 0;
    }
    if (abs(M[f][f]) > abs(M[s][f])) {
        sign *= -1;
        double *tmp = M[s];
        M[s] = M[f];
        M[f] = tmp;
        printf("  Поменять строку [%d] со строкой [%d] и поменять знак\n", f, s);
    }
    double k = M[f][f] == 0 ? 1 : -M[s][f] / M[f][f];
    printf("  Умножить строку [%d] на %f и прибавить к строке [%d]\n\n", f, k, s);
    for (int i = 0; i < N; i++)
        M[s][i] += k * M[f][i];
    Display(M, N);
    return sign;
}

void Display(double **M, const int N) {
    cout << "  ";
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cout << M[i][j] << (j < N - 1 ? "\t" : "\n  ");
}
