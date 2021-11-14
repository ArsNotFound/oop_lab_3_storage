cmake_minimum_required(VERSION 3.20)
project(oop_lab_3_storage)

set(CMAKE_CXX_STANDARD 14)

add_library(oop_lab_3_storage storage.cpp)

add_executable(oop_lab_3_storage_exec main.cpp)