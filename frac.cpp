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

int main()
{
    Fraction f1(2, 5);
    f1.print();

    Fraction f2(3, 8);
    f2.print();

    Fraction f3 = f1 * f2;
    f3.print();

    Fraction f4 = f1 * 2;
    f4.print();

    Fraction f5 = 2 * f2;
    f5.print();

    Fraction f6 = Fraction(1, 2) * Fraction(2, 3) * Fraction(3, 4);
    f6.print();

    return 0;
}
