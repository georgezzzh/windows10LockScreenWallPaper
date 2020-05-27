cmake_minimum_required(VERSION 3.14)
project(LockScreenWallpaper)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS  -static)
add_executable(LockScreenWallpaper main.cpp)