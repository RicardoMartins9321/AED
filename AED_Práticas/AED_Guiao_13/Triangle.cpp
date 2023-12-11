#include "Triangle.h"

#include <cassert>
#include <iostream>
#include <string>
#include <math.h>

#include "Point.h"

Triangle::Triangle(void) {
  // Triangle of sides equal to 1 and centered at (0,0)
  SetCenter(Point(0, 0));
  side1_ = 1.0;
  side2_ = 1.0;
  angle_ = 45.0;
  SetColor("White");
}

Triangle::Triangle(Point center, const std::string& color, double side1,
                    double side2, double angle) {
  // Ensure all the sides are bigger than 0 and that they follow the triangle rule
  assert(side1 > 0.0 && side2 > 0.0 && angle > 0.0 && angle < 180.0);

  SetCenter(center);
  SetColor(color);
  side1_ = side1;
  side2_ = side2;
  angle_ = angle;
}

Triangle::Triangle(double x, double y, const std::string& color, double side1,
                    double side2, double angle) {
  // Ensure all the sides are bigger than 0 and that they follow the triangle rule
  assert(side1 > 0.0 && side2 > 0.0 && angle > 0.0 && angle < 180.0);

  SetCenter(Point(x, y));
  SetColor(color);
  side1_ = side1;
  side2_ = side2;
  angle_ = angle;
}

double Triangle::GetSide1(void) const { return side1_; }
void Triangle::SetSide1(double length) {
  // Ensure that the length is larger than 0.0
  assert(length > 0.0);
  side1_ = length;
}

double Triangle::GetSide2(void) const { return side2_; }
void Triangle::SetSide2(double length) {
  // Ensure that the length is larger than 0.0
  assert(length > 0.0);
  side2_ = length;
}

std::string Triangle::GetClassName(void) const { return "Triangle"; }

double Triangle::Area(void) const {
  return 0.5 * side1_ * side2_ * std::sin(angle_ * M_PI / 180.0);
}

double Triangle::Perimeter(void) const {
    // Calculate the length of the third side using the Law of Cosines
  double side3 = std::sqrt(side1_ * side1_ + side2_ * side2_ - 2 * side1_ * side2_ * std::cos(angle_ * M_PI / 180.0));

    return side1_ + side2_ + side3;
}

std::ostream& operator<<(std::ostream& os, const Triangle& obj) {
    os << "Center: " << obj.GetCenter() << std::endl;
    os << "Color: " << obj.GetColor() << std::endl;
    os << "Side1 = " << obj.GetSide1() << ", Side2 = " << obj.GetSide2() << std::endl;
    os << "Angle = " <<  obj.GetAngle() << std::endl;
    return os;
}

std::istream& operator>>(std::istream& is, Triangle& obj) {
    // Input format: x y color width height
    Point center;
    std::string color;
    double side1, side2, angle;

    is >> center >> color >> side1 >> side2 >> angle;

    assert(side1 > 0.0 && side2 > 0.0 && angle > 0.0 && angle < 180.0);

    obj.SetCenter(center);
    obj.SetColor(color);
    obj.SetSide1(side1);
    obj.SetSide2(side2);
    obj.SetAngle(angle);

    return is;
}