cmake_minimum_required(VERSION 3.11.0)

project(Pizzas 
        LANGUAGES CXX)

set(SRC_LIST
    Pizza.cpp
    Pizzeria.cpp
    Funghi.cpp
    Margerita.cpp)

# library target
add_library(${PROJECT_NAME}-lib STATIC ${SRC_LIST})
target_compile_options(${PROJECT_NAME}-lib 
                      PUBLIC -Wall -Wextra -pedantic -Wconversion)
target_compile_features(${PROJECT_NAME}-lib PUBLIC cxx_std_17)
