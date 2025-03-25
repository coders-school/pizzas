cmake_minimum_required(VERSION 3.11.0)

set(PROJECT_NAME Pizzas)

project ( ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)
set ( SRC_LIST 
    src/Funghi.cpp
    src/Margherita.cpp
    src/Pizza.cpp
    src/Pizzeria.cpp)


add_library( ${PROJECT_NAME}-lib ${SRC_LIST})

add_executable( ${PROJECT_NAME} src/main.cpp)
target_link_libraries( ${PROJECT_NAME} ${PROJECT_NAME}-lib)
target_link_libraries( ${PROJECT_NAME} pthread)

# TODO: Write proper build system :)