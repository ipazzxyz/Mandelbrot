#include "complex.hpp"

#include <cmath>

Complex::Complex() : a(0), b(0) {};
Complex::Complex(double a, double b) : a(a), b(b) {};
Complex& Complex::operator+=(Complex complex) {
  return *this = *this + complex;
}
Complex Complex::operator+(Complex complex) {
  return Complex(a + complex.a, b + complex.b);
}
Complex& Complex::operator-=(Complex complex) {
  return *this = *this - complex;
}
Complex Complex::operator-(Complex complex) { return *this + -complex; }
Complex Complex::operator-() { return Complex(-a, -b); }
Complex& Complex::operator=(Complex complex) {
  a = complex.a;
  b = complex.b;
  return *this;
}
Complex& Complex::operator*=(Complex complex) {
  return *this = *this * complex;
}
Complex Complex::operator*(Complex complex) {
  return Complex(a * complex.a - b * complex.b, a * complex.b + b * complex.a);
}