cmake_minimum_required(VERSION 3.11.0)

project(Pizzas)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

set(SRC_LIST src/Funghi.cpp src/Margherita.cpp src/Pizza.cpp src/Pizzeria.cpp)

add_library(${PROJECT_NAME}-lib STATIC ${SRC_LIST})
set_target_properties(${PROJECT_NAME}-lib PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
target_compile_options(${PROJECT_NAME}-lib PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Werror)

add_executable(${PROJECT_NAME} src/main.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Werror)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib pthread)

enable_testing()
add_executable(${PROJECT_NAME}-ut test/PizzeriaTest.cpp test/test_main.cpp)
set_target_properties(${PROJECT_NAME}-ut PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
target_compile_options(${PROJECT_NAME}-ut PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Werror)
target_include_directories(${PROJECT_NAME}-ut PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/test)
target_link_libraries(${PROJECT_NAME}-ut ${PROJECT_NAME}-lib GTest::gtest_main GTest::gmock)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}-ut)
