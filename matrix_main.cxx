#include <random>
#include <iostream>
#include "matrix.hxx"

using namespace std;

template <typename T>
ostream& operator<<(ostream& os, const Matrix<T>& mat) {
  for (size_t i = 0; i < mat.rows(); ++i) {
    for (size_t j = 0; j < mat.cols(); ++j) {
      os << mat[i][j] << " ";
    }
    
    os << endl;
  }

  return os;
}

int main() {
  Matrix<int> m1(5,5), m2(5,5), m3;
  random_device gen;
  uniform_int_distribution<int> dist(0, 10);

  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      m1[i][j] = dist(gen);
      m2[i][j] = dist(gen);
    }
  }

  cout << m1 << endl << m2 << endl;

  m2 += m1;

  cout << m2 << endl;

  return 0;
}
