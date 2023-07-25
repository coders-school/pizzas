cmake_minimum_required(VERSION 3.11.0)

project(pizzas)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON)

set(SRC_LIST
    src/Funghi.cpp
    src/Margherita.cpp
    src/Pizza.cpp
    src/Pizzeria.cpp)

set(SRC_UT
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
include_directories(test/mocks)
add_library(${PROJECT_NAME}-lib STATIC ${SRC_LIST}) 
target_link_libraries(${PROJECT_NAME}-lib Threads::Threads)

add_executable(${PROJECT_NAME} src/main.cpp)   
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib)


link_libraries(gmock)
add_executable(${PROJECT_NAME}-ut ${SRC_UT})
target_link_libraries(${PROJECT_NAME}-ut ${PROJECT_NAME}-lib GTest::gtest_main)

set_target_properties(${PROJECT_NAME}-lib PROPERTIES ${PROPERTIES})
set_target_properties(${PROJECT_NAME} PROPERTIES ${PROPERTIES})
set_target_properties(${PROJECT_NAME}-ut PROPERTIES ${PROPERTIES})

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}-ut)
