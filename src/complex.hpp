#pragma once

struct Complex {
  double a, b;

  Complex();
  Complex(double, double);
  Complex& operator+=(Complex);
  Complex operator+(Complex);
  Complex& operator-=(Complex);
  Complex operator-(Complex);
  Complex operator-();
  Complex& operator*=(Complex);
  Complex operator*(Complex);
  Complex& operator=(Complex);
};