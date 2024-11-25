#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <string_view>

const double PI{ 3.14159 };

class Shape { // Base Shape class
public:
    // Every shape has a color
    enum Color {
        black,
        red,
        green,
        yellow,
        blue,
        magenta,
        cyan,
        white,
        maxShapeColors,
    };

private:
    Color m_color{};
    bool m_symmetry{};
    int m_sides{};
    std::string m_name{};

public:
    Shape(Color color, bool symmetry, int sides, std::string name)
        : m_color{ color }
        , m_symmetry{ symmetry }
        , m_sides{ sides }
        , m_name{ name }
    {
        std::cout << "Shape constructed.\n";
        std::cout << "Shape color = " << color << '\n';
        std::cout << "Shape symmetry = " << symmetry << '\n';
        std::cout << "Shape sides = " << sides << '\n';
        std::cout << "Shape name = " << name << "\n\n";
    }

    virtual ~Shape() {
        std::cout << "~Shape() destructed\n\n";
    }

    virtual double getPerimeter() const = 0;
    virtual double getArea() const = 0;

    virtual const std::string_view getColorName() const {
        switch(m_color) {
            case black:     return "black";
            case red:       return "red";
            case green:     return "green";
            case yellow:    return "yellow";
            case blue:      return "blue";
            case magenta:   return "magenta";
            case cyan:      return "cyan";
            case white:     return "white";
            default:        return "white";
        }
    }
};

class Circle: public Shape {
private:
    double m_radius;

public:
    Circle(double radius, Color color, bool symmetry, int sides, std::string name)
        : Shape(color, symmetry, sides, name)
        , m_radius{ radius }
    {
        std::cout << "Circle constructed.\n";
        std::cout << "Circle radius = " << radius << '\n';
        std::cout << "Circle color = " << color << '\n';
        std::cout << "Circle symmetry = " << symmetry << '\n';
        std::cout << "Circle sides = " << sides << '\n';
        std::cout << "Circle name = " << name << "\n\n";
    }

    virtual ~Circle() {
        std::cout << "~Circle() destructed.\n\n";
    }

    double getPerimeter() const override {
        return 2 * PI * m_radius;
    }

    double getArea() const override {
        return PI * pow(m_radius, 2);
    }
};

int main() {
    Circle* circle{ new Circle{4.0, Circle::red, true, 0, "circle"} };

    std::cout << "Circle perimeter: " << circle->getPerimeter() << '\n';
    std::cout << "Circle area: " << circle->getArea() << '\n';
    std::cout << "Color chosen: " << circle->getColorName() << '\n';

    delete circle;

    return 0;
}
