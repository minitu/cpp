#include <iostream>
#include <string>

template <typename T>
class Pair1 {
  private:
    T m1, m2;

  public:
    Pair1(T n1, T n2) : m1(n1), m2(n2) {}
    // better to return by reference, but need to duplicate functions to
    // return const
    T first() const { return m1; }
    T second() const { return m2; }
};

template <typename T1, typename T2>
class Pair {
  private:
    T1 m1;
    T2 m2;

  public:
    Pair(T1 n1, T2 n2) : m1(n1), m2(n2) {}
    T1 first() const { return m1; }
    T2 second() const { return m2; }
};

// Unnecessary
/*
template <typename T2>
class Pair<std::string, T2> {
  private:
    std::string m1;
    T2 m2;

  public:
    Pair(std::string n1, T2 n2) : m1(n1), m2(n2) {}
    std::string first() const { return m1; }
    T2 second() const { return m2; }
};
*/

template <typename T>
class StringValuePair : public Pair<std::string, T> {
  public:
    StringValuePair(std::string n1, T n2) : Pair<std::string, T>(n1, n2) {}
};

int main() {
  StringValuePair<int> svp("Hello", 5);
  std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';

  return 0;
}
