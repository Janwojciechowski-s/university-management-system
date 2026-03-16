#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <string>

struct Subject
{
	std::string subject_name;
	std::vector<float> grades;
	int semester;
	Subject(const std::string& n, int s) : subject_name(n), semester(s) {};
	float calculate_average() const;
	void add_grade(float grade);
};

#endif // !SUBJECT_H

