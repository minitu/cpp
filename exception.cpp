#include <iostream>
#include <stdexcept>

class Fraction {
  private:
    int m_numer;
    int m_denom;

  public:
    Fraction(int numer, int denom) {
      if (denom == 0) {
        throw std::runtime_error("");
      }

      m_numer = numer;
      m_denom = denom;
    }

    int numerator() { return m_numer; }
    int denominator() { return m_denom; }
};

int main() {
  int numer, denom;

  std::cout << "Enter the numerator: ";
  std::cin >> numer;

  std::cout << "Enter the denominator: ";
  std::cin >> denom;

  try {
    Fraction frac(numer, denom);
    std::cout << frac.numerator() << "/" << frac.denominator() << std::endl;
  }
  catch (std::exception) {
    std::cout << "Your fraction has an invalid denominator." << std::endl;
  }

  return 0;
}
