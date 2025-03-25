cmake_minimum_required(VERSION 3.11.0)

set(PROJECT_NAME Pizzas)

project ( ${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

set(SRC_LIST
    src/Funghi.cpp
    src/Margherita.cpp
    src/Pizza.cpp
    src/Pizzeria.cpp)


add_library(${PROJECT_NAME}-lib STATIC ${SRC_LIST}) 

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib pthread)



link_libraries(gmock)
add_executable(${PROJECT_NAME}-ut test/test_main.cpp test/PizzeriaTest.cpp)
target_link_libraries(${PROJECT_NAME}-ut ${PROJECT_NAME}-lib GTest::gtest_main)

enable_testing()
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}-ut)

# TODO: Write proper build system :)


