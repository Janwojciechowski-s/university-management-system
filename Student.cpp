#include "Student.h"
using namespace std;
#include<iostream>


Student::Student(const std::string& first_name, const std::string& last_name, const std::string& major) : Person(first_name, last_name), major(major) {}

std::string Student::get_major() const
{
	return this->major;
}

const std::vector<Subject>& Student::get_subjects() const
{
	return this->subjects;
}

void Student::add_subject(const string& subject_name, int semester)
{
	for (const Subject& sub : subjects) {
		if (sub.subject_name == subject_name) {
			throw std::invalid_argument("Student already have this subject!");
		}
	}
	Subject temp_subject(subject_name, semester);
	this->subjects.push_back(temp_subject);
}

void Student::add_grade(const string& subject_name, float grade)
{
	for (Subject& p : this->subjects) {
		if (p.subject_name == subject_name) {
			p.add_grade(grade);
			return;
		}
	}
	throw std::runtime_error("Subject '" + subject_name + "' not found for this student.");
}

float Student::calculate_subject_average(const string& subject_name) const
{
	for (const Subject& p : this->subjects) {
		if (p.subject_name == subject_name)
			return p.calculate_average();
	}
	return 0.0f;
}

float Student::calculate_semester_average(int target_semester) const
{
	float sum = 0;
	int count = 0;
	for (const Subject& p : this->subjects) {
		if (p.semester == target_semester) {
			sum += p.calculate_average();
			++count;
		}
	}
	if (count == 0) {
		return 0.0f;
	}
	return sum / count;
}

bool Student::is_at_risk() const
{
	for (const Subject& p : this->subjects) {
		if (p.calculate_average() < 3.0) {
			return true;
		}
	}
	return false;
}

std::ostream& operator<<(std::ostream& os, const Student& s)
{
	os << "Student: " << s.get_first_name() << " " << s.get_last_name() <<endl;
	os << "Major: " << s.major <<endl;
	if (s.subjects.empty()) {
		os << "Student has no subjects assigned" << endl;
	}
	else {
		for (const Subject& p : s.subjects) {
			os << "Subject name: " << p.subject_name<<" || Grades: ";
			if (p.grades.empty()) {
				os << "No grades";
			}
			else {
				for (float o : p.grades) {
					os << o << " ";
				}
			}
			os << endl;
		}
	}
	return os;
}
