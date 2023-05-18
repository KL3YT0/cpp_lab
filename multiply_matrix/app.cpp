#include <iostream>
#include <vector>
#include <cstdlib> 
#include <ctime> 
#include <chrono>

using namespace std;

void showMatrix(vector<vector<double>> matrix) {
    int N = matrix.size();
    int M = matrix[0].size();

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout << matrix[i][j] << " ";
        }

        cout << endl;
    }
}

vector<vector<double>> createRandomMatrix(int N, int M) {
    vector<vector<double>> matrix(N, vector<double>(M, 11));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            matrix[i][j] = rand() % 100;
        }
    }

    return matrix;
}

/// Умножение матриц классических способом
vector<vector<double>> firstStrategy(vector<vector<double>> fMatrix, vector<vector<double>> sMatrix) {
    int N = fMatrix.size();
    int M = sMatrix[0].size();

    if (N != M) {
        cout << "Houston, we have a problem" << endl;
        exit(0);
    }

    vector<vector<double>> product (N, vector<double>(M, 0));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
          for (int k = 0; k < N; k++) {
            product[i][j] += fMatrix[i][k] * sMatrix[k][j];
          }
        }
    }

    return product;
}

/// Умножение матриц с сохранением строки первой матрицы
vector<vector<double>> secondStrategy(vector<vector<double>> fMatrix, vector<vector<double>> sMatrix) {
    int fRow = fMatrix.size();
    int fCol = fMatrix[0].size();

    int sRow = sMatrix.size();
    int sCol = sMatrix[0].size();

    if (fRow != sCol) {
        cout << "Houston, we have a problem" << endl;
        exit(0);
    }

    vector<vector<double>> product (fCol, vector<double>(sRow, 0));

    for (int i = 0; i < fRow; i++) {
        vector<double> currRow(fCol);

        for (int j = 0; j < fCol; j++) {
            currRow[j] = fMatrix[i][j];
        }

        for (int j = 0; j < sCol; j++) {
            for (int k = 0; k < sRow; k++) {
                product[i][j] += currRow[k] * sMatrix[k][j];
            }
        }
    }

    return product;
}

/// Умножение матриц с сохранением столбца второй матрицы
vector<vector<double>> thirdStrategy(vector<vector<double>> fMatrix, vector<vector<double>> sMatrix) {
    int fRow = fMatrix.size();
    int fCol = fMatrix[0].size();

    int sRow = sMatrix.size();
    int sCol = sMatrix[0].size();

    if (fRow != sCol) {
        cout << "Houston, we have a problem" << endl;
        exit(0);
    }

    vector<vector<double>> product (fCol, vector<double>(sRow, 0));

    for (int i = 0; i < sCol; i++) {
        vector<double> currCol(sRow);
        
        for (int j = 0; j < sRow; j++) {
            currCol[j] = sMatrix[j][i];
        }

        for (int j = 0; j < fRow; j++) {
            for (int k = 0; k < fCol; k++) {
                product[j][i] += currCol[k] * fMatrix[j][k];
            }
        }
    }

    return product;
}

/// Умножение матриц с сохранением столбца и строки
vector<vector<double>> fourthStrategy(vector<vector<double>> fMatrix, vector<vector<double>> sMatrix) {
    int fRow = fMatrix.size();
    int fCol = fMatrix[0].size();

    int sRow = sMatrix.size();
    int sCol = sMatrix[0].size();

    if (fRow != sCol) {
        cout << "Houston, we have a problem" << endl;
        exit(0);
    }

    vector<vector<double>> product (fCol, vector<double>(sRow, 0));

    for (int i = 0; i < fRow; i++) {
        vector<double> currRow(fCol);

        for (int j = 0; j < fCol; j++) {
            currRow[j] = fMatrix[i][j];
        }

        for (int j = 0; j < fCol; j++) {
            vector<double> currCol(fCol);

            for (int k = 0; k < sCol; k++) {
                currCol[k] = sMatrix[k][j];
            }

            for (int k = 0; k < sCol; k++) {
                product[i][j] += currCol[k] * currRow[k];
            }
        }
    }

    return product;
}

void track(
    vector<vector<double>> (*func) (vector<vector<double>>, vector<vector<double>>),
    vector<vector<double>> fMatrix, vector<vector<double>> sMatrix, string name
) {
    auto start = std::chrono::high_resolution_clock::now();
    func(fMatrix, sMatrix);
    auto end = std::chrono::high_resolution_clock::now();

    auto dur = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << name << ": " << dur << " us" << endl;
}

int main() {
    int N = 500;
    int M = 500;

    vector<vector<double>> fMatrix = createRandomMatrix(N, M);
    vector<vector<double>> sMatrix = createRandomMatrix(N, M);

    /* showMatrix(fMatrix);
    cout << endl;
    showMatrix(sMatrix);
    cout << endl; */

    track(firstStrategy, fMatrix, sMatrix, "classic");
    track(secondStrategy, fMatrix, sMatrix, "save row");
    track(thirdStrategy, fMatrix, sMatrix, "save col");
    track(fourthStrategy, fMatrix, sMatrix, "save row & col");
}