#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include <iostream>
#include <string>

#include "Figure.h"
#include "Point.h"

class Triangle : public Figure {
 public:
  Triangle(void);
  Triangle(Point center, const std::string& color, double side1,
            double side2, double angle);
  Triangle(double x, double y, const std::string& color, double side1,
            double side2, double angle);

  double GetSide1(void) const;
  void SetSide1(double side1);
  double GetSide2(void) const;
  void SetSide2(double side2);
  double GetAngle(void) const;
  void SetAngle(double angle);

  std::string GetClassName(void) const;
  double Area(void) const;
  double Perimeter(void) const;

  friend std::ostream& operator<<(std::ostream& os, const Triangle& obj);
  friend std::istream& operator>>(std::istream& is, Triangle& obj);

 private:
  double side1_;
  double side2_;
  double angle_;
};

#endif  // TRIANGLE_H_