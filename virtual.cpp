#include <iostream>

class Point {
    private:
        int m_x = 0;
        int m_y = 0;
        int m_z = 0;

    public:
        Point(int x, int y, int z) : m_x(x), m_y(y), m_z(z) {}

        friend std::ostream& operator<<(std::ostream& out, const Point& p) {
            out << "Point(" << p.m_x << ", " << p.m_y << ", " << p.m_z << ")";
            return out;
        }
};

class Shape {
    public:
        virtual ~Shape() {}
        virtual std::ostream& print(std::ostream& out) const = 0;

        friend std::ostream& operator<<(std::ostream& out, const Shape& s) {
            return s.print(out);
        }
};

class Triangle : public Shape {
    private:
        Point m_a, m_b, m_c;

    public:
        Triangle(const Point &a, const Point &b, const Point &c)
            : m_a(a), m_b(b), m_c(c) {}

        virtual std::ostream& print(std::ostream& out) const override {
            out << "Triangle(" << m_a << ", " << m_b << ", " << m_c << ")";
            return out;
        }
};

class Circle : public Shape {
    private:
        Point m_center;
        int m_radius;

    public:
        Circle(const Point& center, int radius) // need to pass as const reference
            : m_center(center), m_radius(radius) {}

        virtual std::ostream& print(std::ostream& out) const override {
            out << "Circle(" << m_center << ", radius " << m_radius << ")";
            return out;
        }
};

int main() {
    Circle c(Point(1, 2, 3), 7);
    std::cout << c << '\n';

    Triangle t(Point(1, 2, 3), Point(4, 5, 6), Point(7, 8, 9));
    std::cout << t << '\n';

    return 0;
}
