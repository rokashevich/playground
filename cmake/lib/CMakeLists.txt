cmake_minimum_required(VERSION 3.18)
project(mylib)
add_library(mylib SHARED lib.cpp)

install(TARGETS mylib DESTINATION lib)
