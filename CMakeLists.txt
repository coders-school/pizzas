cmake_minimum_required(VERSION 3.11.0)

include(FetchContent)
FetchContent_Delcare(googletest URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip)

set(GTEST_FORCE_SHARED_CRT ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

project(Pizzas)

set(SRC_LIST src/Funghi.cpp src/Margherita.cpp src/Pizza.cpp src/Pizzeria.cpp)

add_library(${PROJECT_NAME}.lib STATIC ${SRC_LIST})
set_target_properties(${PROJECT_NAME}.lib PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} src/main.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}.lib pthread)

enable_testing()

add_executable(PizzerriaTest test/PizzerriaTest.cpp test/test_main.cpp)

target_link_libraries(PizzerriaTest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(PizzerriaTest)