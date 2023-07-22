cmake_minimum_required(VERSION 3.18)
project(aaa)
add_executable(aaa aaa.cpp)

install(TARGETS aaa DESTINATION bin)

message("CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR}")
message("CMAKE_CURRENT_SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}")

if(EXISTS "${CMAKE_SOURCE_DIR}/CMakeLists.txt")
  message("YES")
else()
  message("NO")
endif()