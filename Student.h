#ifndef STUDENT_H
#define STUDENT_H
#include"Person.h"
#include"Subject.h"
#include<vector>
#include<string>

class Student : public Person {
private:
	std::vector<Subject> subjects;
	std::string major;
public:
	Student(const std::string& first_name,const std::string& last_name,const std::string& major);
	~Student() override = default;
	std::string get_major() const;
	const std::vector<Subject>& get_subjects() const;
	void add_subject(const std::string& subject_name, int semester);
	void add_grade(const std::string& subject_name, float grade);
	float calculate_subject_average(const std::string& subject_name) const;
	float calculate_semester_average(int target_semester) const;
	bool is_at_risk() const;
	friend std::ostream& operator<<(std::ostream& os, const Student& s);
};
#endif // !STUDENT_H
