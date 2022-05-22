cmake_minimum_required(VERSION 3.11.0)

# TODO: Write proper build system :)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SRC_LIST src/Funghi.cpp Margherita.cpp Pizza.cpp Pizzeria.cpp)

project(Pizzas)

add_library(lib STATIC SRC_LIST)

add_executable(${PROJECT_NAME} src/main.cpp)
add_executable(${PROJECT_NAME}-ut test/PizzeriaTest.cpp test/test_main.cpp)

set(FLAGS -Wall -Wextra -Werror -Wpedantic - Wconversion -O3)

add_compile_options(lib PRIVATE ${FLAGS})
add_compile_options(${PROJECT_NAME} PRIVATE ${FLAGS})
add_compile_options(${PROJECT_NAME}-ut PRIVATE ${FLAGS})

target_link_libraries(${PROJECT_NAME} lib)
target_link_libraries(${PROJECT_NAME}-ut lib)

enable_testing()
add_test(NAME tests COMMAND ${PROJECT_NAME}-ut)