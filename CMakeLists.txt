# CMakeLists.txt

cmake_minimum_required(VERSION 3.12)

# Project name
project(MyProject)

# Set C++ standard (change to your desired standard)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable
add_executable(MyProject "src/main.cpp")
set_target_properties(MyProject PROPERTIES WIN32_EXECUTABLE TRUE)