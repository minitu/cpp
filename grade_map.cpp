#include <string>
#include <vector>
#include <iostream>

struct StudentGrade
{
    std::string m_name;
    char m_grade;

    StudentGrade(std::string name) : m_name(name) {}
};

class GradeMap
{
    private:
        std::vector<StudentGrade> m_map;

    public:
        GradeMap() {}

        char& operator[](std::string name)
        {
            for (auto& student_grade : m_map)
            {
                if (student_grade.m_name == name) // found student
                {
                    return student_grade.m_grade;
                }
            }

            // student not found, create one and store in vector
            m_map.push_back(StudentGrade(name));
            return (m_map.back().m_grade);
        }
};

int main()
{
    GradeMap grades;
    grades["Joe"] = 'A';
    grades["Frank"] = 'B';
    std::cout << "Joe has a grade of " << grades["Joe"] << '\n';
    std::cout << "Frank has a grade of " << grades["Frank"] << '\n';

    return 0;
}
