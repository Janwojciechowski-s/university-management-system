#include "Deanery.h"
#include <algorithm>
#include<vector>
#include<fstream>
#include<stdexcept>
#include <sstream>
using namespace std;




Deanery::Deanery() {};

Deanery::~Deanery() {};

const std::vector<std::unique_ptr<Student>>& Deanery::get_students() const
{
	return this->students;
}

void Deanery::add_student(std::unique_ptr<Student> new_student)
{
	if (new_student != nullptr) {
		this->students.push_back(move(new_student));
	}
}

bool Deanery::remove_student(const std::string& first_name,const std::string& last_name)
{
	int initial_size = students.size();

	auto it = remove_if(students.begin(), students.end(),
		[&last_name, &first_name](const unique_ptr<Student>& s) {
			return s->get_last_name() == last_name && s->get_first_name() == first_name;	
		});
	students.erase(it, students.end());
	return students.size() < initial_size;
}

bool Deanery::major_exists(const std::string& major)
{
	for (const auto& s : students) {
		if (s->get_major() == major) return true;
	}
	return false;
}


float Deanery::get_student_semester_average(const std::string& first_name,const std::string& last_name, int semester) const
{
	for (const auto& s : students) {
		if (s->get_first_name() == first_name && s->get_last_name() == last_name) {
			return s->calculate_semester_average(semester);
		}
	}
	return 0.0f;
}

Student* Deanery::find_student(const std::string& first_name,const std::string& last_name) const
{
	
	for (const auto& s : students) {
		if (s->get_last_name() == last_name && s->get_first_name() == first_name) {
			return s.get();
		}
	}
	return nullptr;
}

Student* Deanery::find_student(const std::string& first_name, const std::string& last_name)
{
	for (auto& s : students) {
		if (s->get_first_name() == first_name && s->get_last_name() == last_name) {
			return s.get();
		}
	}
	return nullptr;
}

vector <Student*> Deanery::get_at_risk_students() const
{
	vector<Student*> at_risk;
	for (const auto& s : students) {
		if (s->is_at_risk()) {
			at_risk.push_back(s.get());
		}
	}
	return at_risk;
}

Student* Deanery::best_student_semester(int semester) const
{
	if (students.empty() == true)
		return nullptr;

	Student* best = students[0].get();
	for (const auto& s : students) {
		if (best->calculate_semester_average(semester) < s->calculate_semester_average(semester))
			best = s.get();
	}
	return best;
}

float Deanery::get_major_average(const std::string& major, int semester) const
{
	float sum = 0.0;
	int count = 0;
	for (const auto& s : students) {
		if (s->get_major() == major) {
			sum += s->calculate_semester_average(semester);
			++count;
		}
	}
	if (count == 0) {
		return 0.0f;
	}
	return sum/count;
}

void Deanery::save_to_file(const std::string& file_name) const
{
	ofstream file(file_name);
	if (!file.is_open()) {
		throw std::runtime_error("Could not open file: " + file_name);
	}
	for (const auto& s : students) {
		file << s->get_first_name() << ";" << s->get_last_name() << ";" << s->get_major() << ";";

		const auto& subjects = s->get_subjects();
		file << subjects.size();

		for (const Subject& subject : s->get_subjects()) {
			file << ";" <<subject.subject_name << ";" << subject.semester << ";" << subject.grades.size();
			for (const float& grade : subject.grades) {
				file << ";" << grade;
			}
		}
		file << "\n";
	}
}
void Deanery::load_from_file(const std::string& file_name)
{
	ifstream file(file_name);
	if (!file.is_open()) {
		throw std::runtime_error("Could not open file: " + file_name);
	}
	string line;
	while (getline(file, line)) {
		if (line.empty()) {
			continue;
		}
		stringstream ss(line);

		string first_name, last_name, major;
		getline(ss, first_name, ';');
		getline(ss, last_name, ';');
		getline(ss, major, ';');

		auto new_student = make_unique<Student>(first_name, last_name, major);
		
		string subjects_count_str;
		getline(ss, subjects_count_str, ';');
		int subjects_count = stoi(subjects_count_str);
		for (int i = 0; i < subjects_count; ++i) {
			string subject_name, semester_str;
			getline(ss, subject_name, ';');
			getline(ss, semester_str, ';');

			int semester = stoi(semester_str);
			new_student->add_subject(subject_name, semester);

			string grades_count_str;
			getline(ss, grades_count_str, ';');
			int grades_count = stoi(grades_count_str);

			for (int j = 0; j < grades_count; ++j) {

				string grade_str;
				getline(ss, grade_str, ';');
				new_student->add_grade(subject_name, stof(grade_str));
			}
		}
		this->add_student(move(new_student));
	}
}



