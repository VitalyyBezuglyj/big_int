cmake_minimum_required(VERSION 3.6)
project(bigInt)

set(CMAKE_CXX_STANDARD 17)

set(my_compile_flags "-Wall -Wextra -pedantic -O2 -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wcast-qual -Wcast-align  -D_FORTIFY_SOURCE=2 -fstack-protector")
list(APPEND CMAKE_CXX_FLAGS ${my_compile_flags})


add_executable(bigInt main.cpp bigint.h)