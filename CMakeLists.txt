cmake_minimum_required(VERSION 3.11.0)

project(Pizzas)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON)

set(SRC_LIST
    src/Funghi.cpp
    src/Margherita.cpp
    src/Pizza.cpp
    src/Pizzeria.cpp)

set(TEST_SRC_LIST
  test/test_main.cpp
  test/PizzeriaTest.cpp)

find_package(Threads REQUIRED)

include(FetchContent)
FetchContent_Declare(
googletest
GIT_REPOSITORY https://github.com/google/googletest.git
GIT_TAG main
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(src)
add_library(${PROJECT_NAME}-lib STATIC ${SRC_LIST}) 
target_link_libraries(${PROJECT_NAME}-lib pthread)

add_executable(${PROJECT_NAME} src/main.cpp)   
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib)


link_libraries(gmock)
enable_testing()
add_executable(${PROJECT_NAME}-ut ${TEST_SRC_LIST})
target_link_libraries(${PROJECT_NAME}-ut ${PROJECT_NAME}-lib)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}-ut)
