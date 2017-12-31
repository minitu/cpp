#include <iostream>

class Fraction
{
    private:
        int m_numer;
        int m_denom;

    public:
        Fraction(int numer = 0, int denom = 1) : m_numer(numer),
        m_denom(denom)
        {
            reduce();
        }

        void print()
        {
            std::cout << m_numer << "/" << m_denom << std::endl;
        }

        friend Fraction operator*(const Fraction& f1, const Fraction& f2);
        friend Fraction operator*(int i, const Fraction& f);
        friend Fraction operator*(const Fraction& f, int i);
        friend std::ostream& operator<<(std::ostream& out, const Fraction& f);
        friend std::istream& operator>>(std::istream& in, Fraction& f);

        static int gcd(int a, int b)
        {
            return (b == 0) ? (a > 0 ? a : -a) : gcd(b, a % b);
        }

        void reduce()
        {
            int gcd = Fraction::gcd(m_numer, m_denom);
            m_numer /= gcd;
            m_denom /= gcd;
        }
};

Fraction operator*(const Fraction& f1, const Fraction& f2)
{
    return Fraction(f1.m_numer * f2.m_numer, f1.m_denom * f2.m_denom);
}

Fraction operator*(int i, const Fraction& f)
{
    return Fraction(f.m_numer * i, f.m_denom);
}

Fraction operator*(const Fraction& f, int i)
{
    return (i*f);
}

std::ostream& operator<<(std::ostream& out, const Fraction& f)
{
    return (out << f.m_numer << "/" << f.m_denom);
}

std::istream& operator>>(std::istream& in, Fraction& f)
{
    char c;

    in >> f.m_numer;
    in >> c;
    in >> f.m_denom;

    return in;
}

int main()
{
    Fraction f1;
    std::cout << "Enter fraction 1: ";
    std::cin >> f1;

    Fraction f2;
    std::cout << "Enter fraction 2: ";
    std::cin >> f2;

    std::cout << f1 << " * " << f2 << " is " << f1 * f2 << '\n';

    return 0;
}
