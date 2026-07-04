cmake_minimum_required(VERSION 3.11.0)
project(Pizzas)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG main
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(SRC_LIST
    src/Funghi.cpp
    src/Margherita.cpp
    src/Pizza.cpp
    src/Pizzeria.cpp
)

add_library(${PROJECT_NAME}-lib STATIC ${SRC_LIST})

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}-lib pthread)

add_executable(${PROJECT_NAME}-ut test/PizzeriaTest.cpp)
target_include_directories(${PROJECT_NAME}-ut PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(${PROJECT_NAME}-ut PRIVATE ${PROJECT_NAME}-lib pthread GTest::gtest GTest::gtest_main GTest::gmock_main GTest::gmock)

enable_testing()
add_test(NAME PizzeriaTest COMMAND ${PROJECT_NAME}-ut)
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}-ut)
