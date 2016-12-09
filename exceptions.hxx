#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>
#include <exception>

class size_difference : public std::exception {
  public:
    virtual const char* what() const throw() {
      return "Both matrices should have the same dimensions";
    }
};

class row_col_difference : public std::exception {
  public:
    virtual const char* what() const throw() {
      return "Matrices should be NxM and MxK respectively";
    }
};

class jagged_matrix : public std::exception {
  public:
    virtual const char* what() const throw() {
      return "All columns in matrix must be the same size";
    }
};

#endif
