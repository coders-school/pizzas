cmake_minimum_required(VERSION 3.14)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        main
)


set(GTEST_FORCE_SHARED_CRT ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

project(Pizzas)

set(SRC_LIST src/Funghi.cpp src/Margherita.cpp src/Pizza.cpp src/Pizzeria.cpp)

add_library(${PROJECT_NAME}.lib STATIC ${SRC_LIST})
set_target_properties(${PROJECT_NAME}.lib PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} src/main.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}.lib pthread)

add_executable(PizzeriaTest test/PizzeriaTest.cpp)

target_link_libraries(PizzeriaTest gtest_main)

enable_testing()

add_test(NAME pTest COMMAND PizzeriaTest)