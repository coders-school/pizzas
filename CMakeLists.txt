cmake_minimum_required(VERSION 3.14)

project(Pizzas)

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)

FetchContent_MakeAvailable(googletest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



set(SRC_LIST
    src/Funghi.cpp
    src/Margherita.cpp
    src/Pizza.cpp
    src/Pizzeria.cpp
)

add_library(${PROJECT_NAME}-lib STATIC ${SRC_LIST})

target_include_directories(${PROJECT_NAME}-lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_executable(${PROJECT_NAME} src/main.cpp)

add_executable(${PROJECT_NAME}-ut test/PizzeriaTest.cpp)
target_link_libraries(${PROJECT_NAME}-ut PRIVATE ${PROJECT_NAME}-lib GTest::gtest GTest::gtest_main GTest::gmock pthread)

target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}-lib pthread)


enable_testing()
add_test(NAME ${PROJECT_NAME}-ut COMMAND ${PROJECT_NAME}-ut)
