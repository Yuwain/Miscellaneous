#ifndef MATRIX_HXX
#define MATRIX_HXX

#include "concepts.hxx"
#include <iostream>
#include <vector>

template <Number T>
class Matrix {
  private:
    std::vector<std::vector<T>> data;

  public:
    Matrix() = default;
    Matrix(int, int);
    Matrix(const Matrix<T>&);
    Matrix(Matrix<T>&&);
    Matrix<T>& operator=(const Matrix<T>&);
    Matrix<T>& operator=(Matrix<T>&&);

    void resize(int, int);
    size_t rows() const;
    size_t cols() const;
    void set_all(const int);
    std::vector<T>& operator[](const int);
    const std::vector<T>& operator[](const int) const;
    Matrix<T>& operator+=(const Matrix<T>&);
    Matrix<T>& operator-=(const Matrix<T>&);
};

template <Number T>
bool operator==(const Matrix<T>&, const Matrix<T>&);
template <Number T>
bool operator!=(const Matrix<T>&, const Matrix<T>&);
template <Number T>
Matrix<T> operator-(const Matrix<T>&);
template <Number T>
Matrix<T> operator+(const Matrix<T>&, const Matrix<T>&);
template <Number T>
Matrix<T> operator-(const Matrix<T>&, const Matrix<T>&);


/* Definitions */

/* Ctor */
template <Number T>
Matrix<T>::Matrix(int rows, int cols) {
  resize(rows, cols);
}

/* Copy constructor */
template <Number T>
Matrix<T>::Matrix(const Matrix<T>& mat) {
  resize(mat.rows(), mat.cols());

  for (size_t i = 0; i < mat.rows(); ++i) {
    for (size_t j = 0; j < mat.cols(); ++j) {
      data[i][j] = mat[i][j];
    }
  }
}

/* Move constructor */
template <Number T>
Matrix<T>::Matrix(Matrix<T>&& mat) {
  resize(mat.rows(), mat.cols());
  
  for (size_t i = 0; i < mat.rows(); ++i) {
    for (size_t j = 0; j < mat.cols(); ++j) {
      data[i][j] = std::move(mat[i][j]);
    }
  }
}

/* Copy assignment operator */
template <Number T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& mat) {
  resize(mat.rows(), mat.cols());

  for (size_t i = 0; i < mat.rows(); ++i) {
    for (size_t j = 0; j < mat.cols(); ++j) {
      data[i][j] = mat[i][j];
    }
  }

  return *this;
}

/* Move assignment operator */
template <Number T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& mat) {
  resize(mat.rows(), mat.cols());

  for (size_t i = 0; i < mat.rows(); ++i) {
    for (size_t j = 0; j < mat.cols(); ++j) {
      data[i][j] = std::move(mat[i][j]);
    }
  }

  return *this;
}


template <Number T>
void Matrix<T>::resize(int rows, int cols) {
  data.resize(rows);

  for (auto& row : data) {
    row.resize(cols);
  }
}

template <Number T>
size_t Matrix<T>::rows() const {
  return data.size();
}

template <Number T>
size_t Matrix<T>::cols() const {
  if (rows() == 0) {
    return 0;
  }
  return data[0].size();
}

template <Number T>
void Matrix<T>::set_all(const int n) {
  for (size_t i = 0; i < rows(); ++i) {
    for (size_t j = 0; j < cols(); ++j) {
      data[i][j] = n;
    }
  }
}

template <Number T>
std::vector<T>& Matrix<T>::operator[](const int i) {
  return data[i];
}

template <Number T>
const std::vector<T>& Matrix<T>::operator[](const int i) const {
  return data[i];
}

template <Number T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& a) {
  for (size_t i = 0; i < a.rows(); ++i) {
    for (size_t j = 0; j < a.cols(); ++j) {
      data[i][j] += a[i][j];
    }
  }

  return *this;
}

template <Number T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& a) {
  for (size_t i = 0; i < a.rows(); ++i) {
    for (size_t j = 0; j < a.cols(); ++j) {
      data[i][j] -= a[i][j];
    }
  }

  return *this;
}

/* Non-member operator overloads */
template <Number T>
bool operator==(const Matrix<T>& a, const Matrix<T>& b) {
  if (a.rows() != b.rows() || a.cols() != b.cols()) {
    return false;
  }

  for (size_t i = 0; i < a.rows(); ++i) {
    for (size_t j = 0; j < a.cols(); ++j) {
      if (a[i][j] != b[i][j]) {
        return false;
      }
    }
  }
  return true;
}

template <Number T>
bool operator!=(const Matrix<T>& a, const Matrix<T>& b) {
  return !(a == b);
}

template <Number T>
Matrix<T> operator+(const Matrix<T>& a, const Matrix<T>& b) {
  Matrix<T> result = a;
  return result += b;
}

template <Number T>
Matrix<T> operator-(const Matrix<T>& a) {
  Matrix<T> result = a;

  for (size_t i = 0; i < result.rows(); ++i) {
    for (size_t j = 0; j < result.cols(); ++j) {
      result[i][j] *= -1;
    }
  }

  return result;
}

template <Number T>
Matrix<T> operator-(const Matrix<T>& a, const Matrix<T>& b) {
  Matrix<T> result = a;
  return result -= b;
}

#endif
