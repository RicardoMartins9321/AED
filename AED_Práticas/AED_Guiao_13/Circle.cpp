//
// Algoritmos e Estruturas de Dados - 2023/2024
//
// COMPLETE the code, according to Circle.h
//

#include "Circle.h"

#define _USE_MATH_DEFINES

#include <cassert>
#include <cmath>
#include <iostream>
#include <string>

#include "Figure.h"
#include "Point.h"

Circle::Circle(void) {
  // Circle of radius 1 and centered at (0,0)
  SetCenter(Point(0,0));
  radius_ = 1.0;
  SetColor("White");
}

Circle::Circle(Point center, const std::string& color, double length) {
  // Ensure that the radius is larger than 0.0
  assert(length > 0.0);

  SetCenter(center);
  SetColor(color);
  radius_ = length;

}

Circle::Circle(double x, double y, const std::string& color, double length) {
  // Ensure that the radius is larger than 0.0
  assert(length > 0.0);

  SetCenter(Point(x,y));
  SetColor(color);
  radius_ = length;
}

double Circle::GetRadius(void) const { return radius_; }
void Circle::SetRadius(double length) {
  assert(length > 0.0);

  radius_ = length; 
}

std::string Circle::GetClassName(void) const { return "Circle"; }

double Circle::Area(void) const {
  return M_PI * (radius_ * radius_);
}

double Circle::Perimeter(void) const {
  return 2 * radius_ * M_PI;
}

bool Circle::Intersects(const Circle& c) const {
  // |r1 - r2| < dist(C1,C2) < r1 + r2

  double distance_between_centers = GetCenter().DistanceTo(c.GetCenter());

  double sum_of_radii = radius_ + c.radius_;

  double absolute_difference_of_radii = std::abs(radius_ - c.radius_);

  return ((absolute_difference_of_radii < distance_between_centers) &&
          (distance_between_centers < sum_of_radii));
}

std::ostream& operator<<(std::ostream& os, const Circle& obj) {
  os << "Center: " << obj.GetCenter() << std::endl;
  os << "Color: " << obj.GetColor() << std::endl;
  os << "Radius = " << obj.radius_ << std::endl;
  return os;
}

std::istream& operator>>(std::istream& is, Circle& obj) {
  // Input format: x y color radius
  Point center;
  std::string color;
  double radius;

  is >> center >> color >> radius;

  // Ensure that the radius is larger than 0.0
  assert(radius > 0.0);

  obj.SetCenter(center);
  obj.SetColor(color);
  obj.SetRadius(radius);

  return is;
}
