#include <iostream>
#include <memory>
#include <string>
#include "Deanery.h"

using namespace std;

void display_menu() {
    cout << "1. Display all students" << endl;
    cout << "2. Add student (manual)" << endl;
    cout << "3. Add subject to student" << endl;
    cout << "4. Add grade to student" << endl;
    cout << "5. Remove student" << endl;
    cout << "6. Student's semester average" << endl;
    cout << "7. Major's average" << endl;
    cout << "8. Display students at risk" << endl;
    cout << "9. Save data to file" << endl;
    cout << "10. Load data from file" << endl;
    cout << "0. Exit" << endl;
}
void display_student_menu(){
    cout << "1. Add subject to student" << endl;
    cout << "2. Add grades to subject" << endl;
    cout << "0. Finish student setup" << endl;
}

template <typename T>
T get_value(const string& message) {
    T value;
    cout << message;
    while (!(cin >> value)) {
        cout << "Error! Invalid data type. Try again: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    return value;
}

string get_text(const string& message) {
    string temp;
    cout << message;
    if (cin.peek() == '\n') {
        cin.ignore();
    }
    getline(cin, temp);
    return temp;
}

int main() {
    int choice = -1;
    Deanery student_manager;
    while (choice != 0) {
        display_menu();
        choice = get_value<int>("Choice: ");
        switch (choice) {
        case 0:
        {
            cout << "System closed" << endl;
            break;
        }
        case 1: 
        {
            for (const auto& s : student_manager.get_students()) {
                cout << *s << endl;
            }
            break;
        }
        case 2:
        {
            string temp_first_name, temp_last_name, temp_major, temp_subject;
            int student_choice = 0, temp_semester = 0;
            float temp_grade = 0.0f;

            temp_first_name = get_text("Enter student's first name: ");
            temp_last_name = get_text("Enter student's last name: ");
            temp_major = get_text("Enter student's major: ");
            auto new_student = make_unique<Student>(temp_first_name, temp_last_name, temp_major);
            display_student_menu();
            student_choice = get_value<int>("Choice: ");
            while (student_choice != 0) {
                switch (student_choice)
                {
                case 0:
                    break;
                case 1: 
                {
                    temp_subject = get_text("Enter subject name: ");
                    temp_semester = get_value<int>("Enter semester: ");
                    new_student->add_subject(temp_subject, temp_semester);
                    cout << "Subject added successfully." << endl;
                    break;
                }

                case 2: 
                {
                    temp_subject = get_text("Enter subject name for grade: ");
                    do {
                        temp_grade = get_value<float>("Enter grade (or 0 to finish): ");
                        if (temp_grade != 0) {
                            try {
                                new_student->add_grade(temp_subject, temp_grade);
                            }
                            catch (const runtime_error& e) {
                                cout << e.what() << endl;
                                break;
                            }
                            catch (const invalid_argument& e) {
                                cout << "Input error: " << e.what() << endl;
                            }
                        }
                    } while (temp_grade != 0);
                    break;
                }
                default:
                    cout << "Invalid option!!" << endl;
                    break;
                }
                display_student_menu();
                student_choice = get_value<int>("Choice: ");
            }
            student_manager.add_student(move(new_student));
            break;
        }
        case 3: {
            string temp_first_name, temp_last_name, temp_subject;
            int temp_semester;
            temp_first_name = get_text("Enter name: ");
            temp_last_name = get_text("Enter lastname: ");
            Student* found_student = student_manager.find_student(temp_first_name, temp_last_name);
            if (found_student == nullptr) {
                cout << "No student with this name and lastname found " << endl;
                break;
            }
            temp_subject = get_text("Enter subject name: ");
            temp_semester = get_value<int>("Enter subject semester : ");
            try {
                found_student->add_subject(temp_subject, temp_semester);
                cout << "Subject added" << endl;
            }
            catch (const std::invalid_argument& e) {
                cout << e.what() << endl;
            }
            break;
        }
        case 4:
        {
            string f_name, l_name;
            f_name = get_text("Enter student's first name: ");
            l_name = get_text("Enter student's last name: ");

            Student* found_student = student_manager.find_student(f_name, l_name);

            if (found_student == nullptr) {
                cout << "Error: Student not found!" << endl;
            }
            else{
                string subj_name = get_text("Enter subject name: ");
                float grade = 0.0f;

                do {
                    grade = get_value<float>("Enter grade (or 0 to finish): ");

                    if (grade != 0) {
                        try {
                            found_student->add_grade(subj_name, grade);
                            cout << "Grade added!" << endl;
                        }
                        catch (const std::invalid_argument& e) {
                            cout << e.what() << endl;
                        }
                        catch (const std::runtime_error& e) {
                            cout << e.what() << endl;
                            break;
                        }
                    }
                } while (grade != 0);
            }
            break;
        }
        case 5:
        {
            string temp_first_name, temp_last_name;

            temp_first_name = get_text("Enter student's first name: ");
            temp_last_name = get_text("Enter student's last name: ");
            if (student_manager.remove_student(temp_first_name, temp_last_name)) {
                cout << "Student " << temp_first_name << " " << temp_last_name << " has been removed" << endl;
            }
            else {
                cout << "No student found!" << endl;
            }
            break;
        }
        case 6:
        {
            string temp_first_name, temp_last_name;
            int temp_semester;

            temp_first_name = get_text("Enter student's first name: ");
            temp_last_name = get_text("Enter student's last name: ");

            if (student_manager.find_student(temp_first_name, temp_last_name) == nullptr) {
                cout << "Error: Student not found!" << endl;
                break;
            }

            temp_semester = get_value<int>("Enter the semester you want to calculate the average for: ");
            float student_semester_average = student_manager.get_student_semester_average(temp_first_name, temp_last_name, temp_semester);
            if (student_semester_average == 0.0f) {
                cout << "Student doesn't have grades in this semester." << endl;
            }
            else {
                cout << "Student's average for semester " << temp_semester << " is: "
                    << student_semester_average << endl;
            }
            break;
        }
        case 7:
        {
            string temp_major;
            int temp_semester;

            
            temp_major = get_text("Enter the major you want to calculate the average for: ");
            temp_semester = get_value<int>("Enter the semester: ");
            if (!student_manager.major_exists(temp_major)) {
                cout << "Error: Major '" << temp_major << "' does not exist in the database" << endl;
            }
            else {
                float major_average = student_manager.get_major_average(temp_major, temp_semester);
                if (major_average == 0.0f) {
                    cout << "Major doesn't have any grades in this semester." << endl;
                }
                else {
                    cout << "The average for this major is: " << major_average << endl;
                }
            }
            break;
        }
        case 8:
        {
            std::vector <Student*> at_risk_students = student_manager.get_at_risk_students();
            if (at_risk_students.size() == 0) {
                cout << "There are no at risk students" << endl;
            }
            else {
                for (const auto& s : at_risk_students) {
                    cout << *s;
                }
                cout << "End of list." << endl;
            }
            break;
        }
        case 9:
        {
            string file_name;
            file_name = get_text("Enter file name: ");
            try {
                student_manager.save_to_file(file_name);
                cout << "Data saved successfully " << file_name << endl;
            }
            catch(const std::exception& e){
                cout << e.what()<< endl;
            }
            break;
        }
        case 10 :
        {
            string file_name;
            file_name = get_text("Enter file name: ");
            try {
                student_manager.load_from_file(file_name);
                cout << "Data loaded successfully" << endl;
            }
            catch (const exception& e) {
                cout << e.what() << endl;
            }
            break;
        }
        default:
            cout << "Invalid option!!" << endl;
            break;
        }
    }
	return 0;
}
