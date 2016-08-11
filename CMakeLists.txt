cmake_minimum_required (VERSION 2.8.11)
project (pogo-proto-dumper CXX)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED on)

add_executable (pogo-proto-dumper src/main.cpp src/il2cpp.hpp)

