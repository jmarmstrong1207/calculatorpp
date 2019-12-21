cmake_minimum_required(VERSION 3.5)

project(calculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(calculator src/main.cpp src/calcParser.cpp src/calcParser.h src/pemdas.cpp src/pemdas.h src/errorHandler.cpp src/errorHandler.h)

