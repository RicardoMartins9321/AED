//
// Algoritmos e Estruturas de Dados - 2023/2024
//
// COMPLETE the code, according to Square.h
//

#include "Square.h"

#include <cassert>
#include <iostream>
#include <string>

#include "Point.h"
#include "Rectangle.h"

Square::Square() {
    SetCenter(Point(0, 0));
    SetColor("White");
    SetWidth(1.0);
    SetHeight(1.0);
}

Square::Square(Point center, const std::string& color, double length) {
    assert(length > 0.0);

    SetCenter(center);
    SetColor(color);
    SetWidth(length);
    SetHeight(length);
}

Square::Square(double x, double y, const std::string& color, double length) {
    assert(length > 0.0);

    SetCenter(Point(x, y));
    SetColor(color);
    SetWidth(length);
    SetHeight(length);
}

double Square::GetEdgeLength(void) const {
    // Since it's a square, width and height are the same
    return GetWidth();
}

void Square::SetEdgeLength(double length) {
    assert(length > 0.0);

    SetWidth(length);
    SetHeight(length);
}

std::string Square::GetClassName(void) const { return "Square"; }

std::ostream& operator<<(std::ostream& os, const Square& obj) {
    os << "Center: " << obj.GetCenter() << std::endl;
    os << "Color: " << obj.GetColor() << std::endl;
    os << "Edge Length = " << obj.GetEdgeLength() << std::endl;
    return os;
}

std::istream& operator>>(std::istream& is, Square& obj) {
    // Input format: x y color edgeLength
    Point center;
    std::string color;
    double edgeLength;

    is >> center >> color >> edgeLength;

    assert(edgeLength > 0.0);

    obj.SetCenter(center);
    obj.SetColor(color);
    obj.SetEdgeLength(edgeLength);

    return is;
}
