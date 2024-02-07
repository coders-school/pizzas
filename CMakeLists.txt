cmake_minimum_required(VERSION 3.11.0)

project(Pizzas)


include(FetchContent)
FetchContent_Declare (
    googletest
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
set(TEST_SRC_LIST
    test/PizzeriaTest.cpp)

# add tests sources as library
add_library(${PROJECT_NAME}-gt-lib STATIC ${TEST_SRC_LIST})
target_compile_options(${PROJECT_NAME}-gt-lib PRIVATE ${FLAGS})
target_compile_features(${PROJECT_NAME}-gt-lib PRIVATE cxx_std_17)

add_executable(${PROJECT_NAME}-gt test/test_main.cpp)
target_link_libraries(${PROJECT_NAME}-gt ${PROJECT_NAME}-gt-lib ${PROJECT_NAME}-lib gtest gtest_main)
target_compile_options(${PROJECT_NAME}-gt PRIVATE ${FLAGS})
target_compile_features(${PROJECT_NAME}-gt PRIVATE cxx_std_17)

enable_testing()
add_test(NAME ${PROJECT_NAME}-gt COMMAND ${PROJECT_NAME}-gt)
