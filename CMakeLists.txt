cmake_minimum_required(VERSION 3.20)

# TODO: Write proper build system :)
project(pizzas CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

add_executable(pizzas 
    src/main.cpp
    src/Pizza.cpp
    src/Pizzeria.cpp
    src/Margherita.cpp
    src/Funghi.cpp
)

target_include_directories(pizzas PRIVATE src)
