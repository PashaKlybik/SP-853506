cmake_minimum_required(VERSION 3.17)
project(Enroll32)

set(CMAKE_CXX_STANDARD 20)

add_executable(Enroll32 WIN32 main.cpp Constants.h Views.h Actions.h)