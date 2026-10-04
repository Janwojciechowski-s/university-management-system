# University Management System (C++)



Console application for managing student data, grades, and subjects.



## Features

- Adding, searching, and removing students.

- Assigning grades and subjects to students.

- Calculating average grades for semesters and majors.

- Saving and loading data from text files.



## Technical Details

- Memory Management: using smart pointers (`std::unique_ptr`) to avoid memory leaks.

- Error Handling: using `try-catch` blocks for data validation.

- Data Storage: using `std::vector` to store the list of students.

- Object-Oriented Programming: code organized into modular classes for better maintainability.



## How to Run

**Prerequisites:**
```bash
sudo apt update && sudo apt install -y build-essential cmake

# Configure and build
cmake -B build
cmake --build build

# Run executable
./build/UniversityManagementSystem
```