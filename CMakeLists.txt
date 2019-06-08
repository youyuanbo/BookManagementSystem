cmake_minimum_required(VERSION 3.12)
project(BookManagementSystem)

set(CMAKE_CXX_STANDARD 14)

add_executable(BookManagementSystem main.cpp
        cpp/Login.cpp
        cpp/Manager.cpp
        cpp/Reader.cpp
        cpp/BorrowInformation.cpp)

