cmake_minimum_required(VERSION 3.11.0)
project(pizzas)

SET(CMAKE_CXX_STANDARD 17)

# Google Test
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG main
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Pthreads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# File sources
SET(SRC_LIST
        src/Funghi.cpp
        src/Margherita.cpp
        src/Pizza.cpp
        src/Pizzeria.cpp
        )

set(SRC_TESTS_LIST
        test/test_main.cpp
        test/PizzeriaTest.cpp
        )

# Library
add_library(${PROJECT_NAME}-lib STATIC ${SRC_LIST})
target_link_libraries(${PROJECT_NAME}-lib Threads::Threads)

# Application build
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib)

# Tests build
enable_testing()
link_libraries(gmock)
add_executable(${PROJECT_NAME}-ut ${SRC_TESTS_LIST})
target_link_libraries(${PROJECT_NAME}-ut ${PROJECT_NAME}-lib)
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}-ut)
