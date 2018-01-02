#include <iostream>
#include <string>

class Fruit {
    private:
        std::string m_name;
        std::string m_color;

    public:
        Fruit(std::string name, std::string color) : m_name(name), m_color(color) {}
        std::string getName() const { return m_name; }
        std::string getColor() const { return m_color; }
};

class Apple : public Fruit {
    private:
        double m_fiber;

    public:
        Apple(std::string name, std::string color, double fiber) :
            Fruit(name, color), m_fiber(fiber) {}
        
        friend std::ostream& operator<<(std::ostream& out, const Apple& a);
};

class Banana : public Fruit {
    public:
        Banana(std::string name, std::string color) : Fruit(name, color) {}

        friend std::ostream& operator<<(std::ostream& out, const Banana& b);
};

std::ostream& operator<<(std::ostream& out, const Apple& a) {
    return (out << "Apple(" << a.getName() << ", " << a.getColor() << ", " <<
            a.m_fiber << ")" << std::endl);
}

std::ostream& operator<<(std::ostream& out, const Banana& b) {
    return (out << "Banana(" << b.getName() << ", " << b.getColor() << ")" <<
            std::endl);
}

int main() {
    const Apple a("Red delicious", "red", 4.2);
    std::cout << a;

    const Banana b("Cavendish", "yellow");
    std::cout << b;

    return 0;
}
