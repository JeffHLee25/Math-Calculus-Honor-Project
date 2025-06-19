#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <cmath>
#include <iostream>
using namespace std;

struct Vector2D {
  double x, y;

  Vector2D(double x = 0.0, double y = 0.0) : x(x), y(y) {}

  // dot product
  double magnitude() const { return sqrt(x * x + y * y); }

  Vector2D normalize() const {
    double mag = magnitude();
    return (mag == 0) ? Vector2D(0, 0) : Vector2D(x / mag, y / mag);
  }

  Vector2D crossZ(const Vector2D& other) const {
    return Vector2D(0, x * other.y - y * other.x);
  }

  Vector2D operator+(const Vector2D& other) const {
    return Vector2D(x + other.x, y + other.y);
  }

  Vector2D operator-(const Vector2D& other) const {
    return Vector2D(x - other.x, y - other.y);
  }

  Vector2D scalarMultiply(double scalar) const {
    return Vector2D(x * scalar, y * scalar);
  }
  double dot(const Vector2D& other) const {
     return x * other.x + y * other.y; 
}

  void print() const { cout << "(" << x << ", " << y << ")"; }
};

#endif
