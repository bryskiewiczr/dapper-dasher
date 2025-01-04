cmake_minimum_required(VERSION 3.30)
project(02_dapper_dasher)

set(CMAKE_CXX_STANDARD 20)

add_executable(02_dapper_dasher dapper_dasher.cpp)

# Include Raylib headers and link its library
include_directories(C:/raylib/include)
target_link_libraries(02_dapper_dasher C:/raylib/lib/libraylib.a)

# Link additional libraries (required by Raylib on Windows)
target_link_libraries(02_dapper_dasher gdi32 winmm shell32)
