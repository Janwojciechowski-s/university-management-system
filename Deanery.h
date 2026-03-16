#ifndef DEANERY_H
#define DEANERY_H
#include"Student.h"
#include <memory>

class Deanery {
private:
	std::vector<std::unique_ptr<Student>> students;
public:
	Deanery();
	~Deanery();
	const std::vector<std::unique_ptr<Student>>& get_students() const;
	void add_student(std::unique_ptr <Student> new_student);
	bool remove_student(const std::string& first_name, const std::string& last_name);
	bool major_exists(const std::string& major);
	float get_student_semester_average(const std::string& first_name, const std::string& last_name, int semester) const;
	Student* find_student(const std::string& first_name, const std::string& last_name) const;
	Student* find_student(const std::string& first, const std::string& last);
	std::vector <Student*> get_at_risk_students() const;
	Student* best_student_semester(int semester) const;
	float get_major_average(const std::string& major, int semester) const;
	void save_to_file(const std::string& file_name) const;
	void load_from_file(const std::string& file_name);
};
#endif // !DEANERY_H