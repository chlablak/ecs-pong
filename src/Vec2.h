/**
 * File: Vec2.h
 * Info: 2D Vector class and utilities
 * Author: chlablak
 * Date: 2017-12-13
 */

#ifndef VEC2_H
#define VEC2_H

#include <ostream>
#include <cmath>

struct Vec2
{
  double x;
  double y;

  Vec2& operator+=(Vec2 const& b)
  {
    x += b.x;
    y += b.y;
    return *this;
  }

  Vec2& operator-=(Vec2 const& b)
  {
    x -= b.x;
    y -= b.y;
    return *this;
  }

  Vec2& operator/=(double v)
  {
    x /= v;
    y /= v;
    return *this;
  }

  Vec2& operator*=(double v)
  {
    x *= v;
    y *= v;
    return *this;
  }

  double length() const
  {
    return std::sqrt(length_squared());
  }

  double length_squared() const
  {
    return x*x + y*y;
  }

  static double dot_product(Vec2 const& a, Vec2 const& b)
  {
    return a.x * b.x + a.y * b.y;
  }

  static Vec2 normalize(Vec2 const& a)
  {
    double len = a.length();
    return Vec2{a.x / len, a.y / len};
  }
};

Vec2 operator-(Vec2 const& a)
{
  return Vec2{-a.x, -a.y};
}

Vec2 operator-(Vec2 const& a, Vec2 const& b)
{
  return Vec2(a) -= b;
}

Vec2 operator+(Vec2 const& a, Vec2 const& b)
{
  return Vec2(a) += b;
}

Vec2 operator/(Vec2 const& a, double v)
{
  return Vec2(a) /= v;
}

Vec2 operator*(double v, Vec2 const& a)
{
  return Vec2(a) *= v;
}

bool operator==(Vec2 const& a, Vec2 const& b)
{
  return std::abs(a.x - b.x) < 0.001 && std::abs(a.y - b.y) < 0.001;
}

std::ostream& operator<<(std::ostream& os, Vec2 const& a)
{
  return os << '(' << a.x << ';' << a.y << ')';
}

#endif // VEC2_H
