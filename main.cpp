#include <iostream>
#include <vector>

using namespace std;


class DeterminantCalculator {
private:
  vector<vector<long long>> matrix;

public:

  DeterminantCalculator(int n): matrix(n, vector<long long>(n, 0)) {}

  void setInputMatrix() {
    int n = matrix.size();
    cout << "Enter the elements of the " << n << "x" << n << " matrix" << endl;

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        cout << "Matrix[" << i+1 << "][" << j+1 << "]: ";
        cin >> matrix[i][j];
      }
    }
  }

  long long calculateDeterminant() {
    return determinant(matrix);
  }

private:
  vector<vector<long long>> createSubmatrix(const vector<vector<long long>>& matrix, int excludedRow, int excludedCol) {
    int n = matrix.size();
    vector<vector<long long>> submatrix(n-1, vector<long long>(n-1, 0));

    for (int i = 1; i < n; i++) {
      int submatrixRow = i - 1;
      for (int j = 0, col = 0; j < n; j++) {
        if (j != excludedCol) {
          submatrix[submatrixRow][col] = matrix[i][j];
          col++;
        }
      }
    }
    return submatrix;
  }

  long long determinant(vector<vector<long long>> matrix) {
      int n_rows = matrix.size();
      int n_cols = matrix[0].size();

      if (n_rows != n_cols) {
          cerr << "Input matrix must be square (NxN)." << endl;
          return 0;
      }

      if (n_rows == 1) {
          return matrix[0][0];
      }

      if (n_rows == 2) {
          return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
      }

      long long determinant_value = 0;

      for (int j = 0; j < n_cols; j++) {
          int sign = (j % 2 == 0) ? 1 : -1;
          vector<vector<long long>> submatrix = createSubmatrix(matrix, 0, j);
          long long submatrix_determinant = determinant(submatrix);
          determinant_value += sign * matrix[0][j] * submatrix_determinant;
      }

      return determinant_value;
  }
};

int main() {
  int n;
  cout << "Enter the size of the matrix (N): ";
  cin >> n;

  DeterminantCalculator calculator(n);
  calculator.setInputMatrix();

  long long det = calculator.calculateDeterminant();
  cout << "Determinant: " << det << endl;

  return 0;
}
