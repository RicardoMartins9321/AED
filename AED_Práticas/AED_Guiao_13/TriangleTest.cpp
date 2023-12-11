#include <iostream>

#include "Point.h"
#include "Triangle.h"

int main(void) {
  Triangle triangle_1;
  std::cout << triangle_1 << std::endl;

  Triangle triangle_2(0.0, 0.0, "yellow", 2, 5, 78);
  std::cout << triangle_2 << std::endl;

  Triangle triangle_3(1.0, 0.0, "red", 10, 50, 35);
  std::cout << triangle_3 << std::endl;

  Point p1(2, 2);
  Triangle triangle_4(p1, "blue", 4, 10, 66), triangle_5;
  std::cout << "Insert Triangle Info:" << std::endl;
  std::cin >> triangle_5;
  std::cout << std::endl;

  std::cout << "triangle_4: " << triangle_4 << std::endl << "triangle_5: " << triangle_5 << std::endl;
  std::cout << "Area: triangle_4 = " << triangle_4.Area() << "; triangle_5 = " << triangle_5.Area()
            << std::endl;
  std::cout << "Perimeter: triangle_4 = " << triangle_4.Perimeter()
            << "; triangle_5 = " << triangle_5.Perimeter() << std::endl;
  std::cout << std::endl;

  Triangle triangle_6(triangle_2);
  Triangle triangle_7 = triangle_6;
  std::cout << "triangle_6: " << triangle_6 << std::endl << "triangle_7: " << triangle_7 << std::endl;

  return 0;
}