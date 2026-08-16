cmake_minimum_required(VERSION 3.11.0)
project(Pizzas)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_LIST 
src/Funghi.cpp
src/Margherita.cpp
src/Pizza.cpp
src/Pizzeria.cpp
)

set(TEST_SRC_LIST
test/PizzeriaTest.cpp 
)
add_executable(${PROJECT_NAME} src/main.cpp)
add_library(${PROJECT_NAME}-lib STATIC ${SRC_LIST})
target_include_directories(${PROJECT_NAME}-lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}-lib pthread)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(${PROJECT_NAME}-ut 
${TEST_SRC_LIST})

target_link_libraries(${PROJECT_NAME}-ut
  GTest::gtest_main
  GTest::gmock
  ${PROJECT_NAME}-lib 
)
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}-ut)