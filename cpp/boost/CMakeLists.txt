cmake_minimum_required(VERSION 3.10.0)
project(httpd)

set(BOOST_ROOT ${PROJECT_SOURCE_DIR}/boost)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_NO_SYSTEM_PATHS ON)
find_package(Boost 1.74 REQUIRED COMPONENTS system program_options)
include_directories (SYSTEM ${Boost_INCLUDE_DIR})

add_executable(httpd httpd.cpp)
find_package(Threads REQUIRED)
target_link_libraries(httpd PRIVATE Threads::Threads)
