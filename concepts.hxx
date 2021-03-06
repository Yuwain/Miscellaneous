#ifndef CONCEPTS_H
#define CONCEPTS_H

template <typename T>
concept bool Number = requires(T a, T b) {
  {a + b} -> T;
  {a - b} -> T;
  {a * b} -> T;
  {a / b} -> T;
  {-a} -> T;

  {a += b} -> T&;
  {a -= b} -> T&;
  {a *= b} -> T&;
  {a /= b} -> T&;

  {T{0}};
};

#endif
