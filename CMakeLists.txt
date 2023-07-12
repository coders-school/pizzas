cmake_minimum_required(VERSION 3.11.0)

# TODO: Write proper build system :)

project(Pizzas)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

Include(FetchContent)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(SRC_LIST
    src/Funghi.cpp
    src/Margherita.cpp
    src/Pizza.cpp
    src/Pizzeria.cpp)

add_library(${PROJECT_NAME}-lib STATIC ${SRC_LIST})

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib pthread)

enable_testing()

add_executable(${PROJECT_NAME}-ut test/test_main.cpp)
target_link_libraries(${PROJECT_NAME}-ut ${PROJECT_NAME}-lib test/PizzeriaTest.cpp GTest::gtest_main GTest::gmock GTest::gmock_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}-ut)
