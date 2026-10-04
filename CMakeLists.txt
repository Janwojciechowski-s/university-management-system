cmake_minimum_required(VERSION 3.20)
project(UniversityManagementSystem)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}
    Main.cpp
    Deanery.cpp
    Person.cpp
    Student.cpp
    Subject.cpp    
)

