cmake_minimum_required(VERSION 3.23)
project(Files_Managment)

set(CMAKE_CXX_STANDARD 14)

add_executable(Files_Managment main.cpp Emp&Dept.h Employee.cpp Department.cpp Functions.cpp)
