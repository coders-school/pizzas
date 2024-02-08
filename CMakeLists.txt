cmake_minimum_required(VERSION 3.11.0)

project(Pizzas)


include(FetchContent)
FetchContent_Declare (
    GTest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG main
)

find_library(PTHREAD_LIB pthread)

set(SRC_LIST
    src/Funghi.cpp
    src/Margherita.cpp
    src/Pizza.cpp
    src/Pizzeria.cpp)

set(FLAGS -Wall -Wextra -Werror -pedantic -Wconversion)

# add sources as library
add_library(${PROJECT_NAME}-lib STATIC ${SRC_LIST})
target_compile_options(${PROJECT_NAME}-lib PRIVATE ${FLAGS})
target_compile_features(${PROJECT_NAME}-lib PRIVATE cxx_std_17)

# main source code
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib ${PTHREAD_LIB})
target_compile_options(${PROJECT_NAME} PRIVATE ${FLAGS})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# tests
enable_testing()

set(PROJECT_NAME_TEST ${PROJECT_NAME}-gt)

set(TEST_SRC_LIST
    test/PizzeriaTest.cpp)

# add tests sources as library
#add_library(${PROJECT_NAME_TEST}-lib STATIC ${TEST_SRC_LIST})
#target_compile_options(${PROJECT_NAME_TEST}-lib PRIVATE ${FLAGS})
#target_compile_features(${PROJECT_NAME_TEST}-lib PRIVATE cxx_std_17)

add_executable(${PROJECT_NAME_TEST} test/PizzeriaTest.cpp)
target_link_libraries(${PROJECT_NAME_TEST} ${PROJECT_NAME}-lib gtest gtest_main)
target_compile_options(${PROJECT_NAME_TEST} PRIVATE ${FLAGS})
target_compile_features(${PROJECT_NAME_TEST} PRIVATE cxx_std_17)

add_test(NAME ${PROJECT_NAME}Tests COMMAND ${PROJECT_NAME_TEST})
#gtest_discover_tests(${PROJECT_NAME_TEST})
