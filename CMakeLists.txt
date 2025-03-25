cmake_minimum_required(VERSION 3.11.0)

set(PROJECT_NAME Pizzas)

project ( ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)
set (SRC_LIST 
    Funghi.cpp
    Margherita.cpp
    Pizza.cpp
    Pizzeria.cpp)


add_library( ${PROJECT_NAME}-lib STATIC ${SRC_LIST})

add_executable( ${PROJECT_NAME} main.cpp)
target_link_libraries( ${PROJECT_NAME} ${PROJECT_NAME}-lib)
target_link_libraries( ${PROJECT_NAME} pthread)


# TODO: Write proper build system :)