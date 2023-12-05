cmake_minimum_required(VERSION 3.11.0)
project(pizzas)

set(PIZZASRC ./src)
set(TESTSRC ./test/)

add_library(pizza STATIC ${PIZZASRC}/Pizza.cpp ${PIZZASRC}/Funghi.cpp ${PIZZASRC}/Margherita.cpp)
target_compile_features(pizza PUBLIC cxx_std_20)

add_library(pizzeria STATIC ${PIZZASRC}/Pizzeria.cpp)
target_compile_features(pizzeria PUBLIC cxx_std_20)
target_link_libraries(pizzeria pizza)

add_executable(${PROJECT_NAME} ${PIZZASRC}/main.cpp)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_link_libraries(${PROJECT_NAME} pizzeria pizza)

#add_library(tests STATIC ${TESTSRC}/PizzeriaTest.cpp)
#target_compile_features(tests PUBLIC cxx_std_20)
#target_include_directories(tests PUBLIC ./src)

#include(FetchContent)

#FetchContent_Declare(
#  googletest
#  GIT_REPOSITORY https://github.com/google/googletest.git
#  GIT_TAG        release-1.8.0
#)

# FetchContent_GetProperties(googletest)
# if(NOT googletest_POPULATED)
#   FetchContent_Populate(googletest)
#   add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
# endif()

# add_executable(${PROJECT_NAME}-test ${TESTSRC}/test_main.cpp)
# target_compile_features(${PROJECT_NAME}-test PUBLIC cxx_std_20)
# target_include_directories(tests PUBLIC /usr/include/gmock)
# target_include_directories(tests PUBLIC /usr/include/gtest)

# enable_testing()
# add_test(NAME test_main COMMAND ${PROJECT_NAME}-test)
