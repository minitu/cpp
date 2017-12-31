#include <string>
#include <iostream>

class Mystring
{
    private:
        std::string m_string;

    public:
        Mystring(std::string string="") : m_string(string) {}

        std::string operator()(int index, int n_chars)
        {
            std::string ret;
            for (int i = 0; i < n_chars; ++i)
            {
                ret += m_string[index++];
            }

            return ret;
        }
};

int main()
{
    Mystring string("Hello, world!");
    std::cout << string(7, 5);

    return 0;
}
