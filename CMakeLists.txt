cmake_minimum_required(VERSION 3.10)
project(binclock)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

add_executable(binclock
   src/main.cpp
   src/utils/split.cpp
   src/instructions.cpp
   src/utils/files.cpp
)
target_compile_features(binclock PUBLIC cxx_std_20)
target_include_directories(binclock PUBLIC src)