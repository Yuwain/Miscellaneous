#ifndef MATRIX_HXX
#define MATRIX_HXX

#include "concepts.hxx"
#include "exceptions.hxx"
#include <vector>

using std::size_t;

template <Number T>
class Matrix {
  private:
    std::vector<std::vector<T>> data;

  public:
    Matrix() = default;
    Matrix(const size_t, const size_t);
    Matrix(const std::vector<std::vector<T>>&);
    Matrix(const Matrix<T>&);
    Matrix(Matrix<T>&&);
    Matrix<T>& operator=(const Matrix<T>&);
    Matrix<T>& operator=(Matrix<T>&&);

    void resize(const size_t, const size_t);
    size_t rows() const;
    size_t cols() const;
    void set_all(const int);
    T& at(const size_t, const size_t);
    const T& at(const size_t, const size_t) const;
    Matrix<T>& operator+=(const Matrix<T>&);
    Matrix<T>& operator-=(const Matrix<T>&);
    Matrix<T>& operator*=(const Number);
    Matrix<T> operator*(const Matrix<T>&) const;
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
template <Number T>
Matrix<T> operator*(const Matrix<T>&, const T);
template <Number T>
Matrix<T> operator*(const T, const Matrix<T>&);


/* Definitions */

/* Ctor */
template <Number T>
Matrix<T>::Matrix(const size_t rows, const size_t cols) {
  resize(rows, cols);
}

template <Number T>
Matrix<T>::Matrix(const std::vector<std::vector<T>>& vec) {
  if (vec.size() != 0) {
    size_t dim = vec[0].size();
    for (auto& row : vec) {
      if (row.size() != dim) {
        throw jagged_matrix();
      }
    }
  }
  data = vec;
}

/* Copy constructor */
template <Number T>
Matrix<T>::Matrix(const Matrix<T>& mat) {
  resize(mat.rows(), mat.cols());

  for (size_t i = 0; i < mat.rows(); ++i) {
    for (size_t j = 0; j < mat.cols(); ++j) {
      this->at(i, j) = mat.at(i, j);
    }
  }
}

/* Move constructor */
template <Number T>
Matrix<T>::Matrix(Matrix<T>&& mat) {
  resize(mat.rows(), mat.cols());
  
  for (size_t i = 0; i < mat.rows(); ++i) {
    for (size_t j = 0; j < mat.cols(); ++j) {
      this->at(i, j) = std::move(mat.at(i, j));
    }
  }
}

/* Copy assignment operator */
template <Number T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& mat) {
  resize(mat.rows(), mat.cols());

  for (size_t i = 0; i < mat.rows(); ++i) {
    for (size_t j = 0; j < mat.cols(); ++j) {
      this->at(i, j) = mat.at(i, j);
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
      this->at(i, j) = std::move(mat.at(i, j));
    }
  }

  return *this;
}


template <Number T>
void Matrix<T>::resize(const size_t rows, const size_t cols) {
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
      this->at(i, j) = n;
    }
  }
}

template <Number T>
T& Matrix<T>::at(const size_t i, const size_t j) {
  return data.at(i).at(j);
}

template <Number T>
const T& Matrix<T>::at(const size_t i, const size_t j) const {
  return data.at(i).at(j);
}

template <Number T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& a) {
  if (a.rows() != rows() || a.cols() != cols()) {
    throw size_difference();
  }
  for (size_t i = 0; i < a.rows(); ++i) {
    for (size_t j = 0; j < a.cols(); ++j) {
      this->at(i, j) += a.at(i, j);
    }
  }

  return *this;
}

template <Number T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& a) {
  if (a.rows() != rows() || a.cols() != cols()) {
    throw size_difference();
  }
  for (size_t i = 0; i < a.rows(); ++i) {
    for (size_t j = 0; j < a.cols(); ++j) {
      this->at(i, j) -= a.at(i, j);
    }
  }

  return *this;
}

template <Number T>
Matrix<T>& Matrix<T>::operator*=(const Number num) {
  for (size_t i = 0; i < rows(); ++i) {
    for (size_t j = 0; j < cols(); ++j) {
      this->at(i, j) *= num;
    }
  }
  return *this;
}

template <Number T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& b) const {
  if (this->cols() != b.rows()) {
    throw row_col_difference();
  }
  int sum;
  Matrix<T> result(this->rows(), b.cols());

  for (size_t i = 0; i < result.rows(); ++i) {
    for (size_t j = 0; j < result.cols(); ++j) {
      sum = 0;
      for (size_t k = 0; k < this->cols(); ++k) {
        sum += this->at(i, k) * b.at(k, j);
      }
      result.at(i, j) = sum;
    }
  }
  return result;
}

/* Non-member operator overloads */
template <Number T>
bool operator==(const Matrix<T>& a, const Matrix<T>& b) {
  if (a.rows() != b.rows() || a.cols() != b.cols()) {
    return false;
  }

  for (size_t i = 0; i < a.rows(); ++i) {
    for (size_t j = 0; j < a.cols(); ++j) {
      if (a.at(i, j) != b.at(i, j)) {
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
      result.at(i, j) *= -1;
    }
  }

  return result;
}

template <Number T>
Matrix<T> operator-(const Matrix<T>& a, const Matrix<T>& b) {
  Matrix<T> result = a;
  return result -= b;
}

template <Number T>
Matrix<T> operator*(const Matrix<T>& mat, const T num) {
  Matrix<T> result = mat;
  return result *= num;
}

template <Number T>
Matrix<T> operator*(const T num, const Matrix<T>& mat) {
  Matrix<T> result = mat;
  return result *= num;
}

#endif
