#include "Subject.h"
#include <stdexcept>
#include <numeric>
using namespace std;
float Subject::calculate_average() const
{
    if (this->grades.empty()) {
        return 0.0f;
    }
    float sum = 0;
    sum = accumulate(grades.begin(), grades.end(), 0.0f);

    return sum / this->grades.size();

}

void Subject::add_grade(float grade)
{
    if (grade > 5.0f || grade < 2.0f) {
        throw std::invalid_argument("Grade out of range (2.0 - 5.0)!!");
    }
    this->grades.push_back(grade);
}
