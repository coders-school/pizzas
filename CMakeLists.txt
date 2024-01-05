cmake_minimum_required(VERSION 3.11.0)

project(Pizzas) 

# set(FLAGS -Wall -Wextra -Werror -pedantic -Wconversion -lstdc+ -Ofast)
set(FLAGS -lstdc+ -Ofast)
set(SRC_LIST src/Funghi.cpp src/Margherita.cpp src/Pizza.cpp src/Pizzeria.cpp)
set(TEST_SRC_LIST test/PizzeriaTest.cpp test/test_main.cpp)

include_directories(src)
include_directories(test)
Include(FetchContent)

FetchContent_Declare(
  googletest 
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(${PROJECT_NAME}-lib STATIC ${SRC_LIST})
target_compile_options(${PROJECT_NAME}-lib PUBLIC ${FLAGS})
target_compile_features(${PROJECT_NAME}-lib PUBLIC cxx_std_17)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib pthread)

add_executable(${PROJECT_NAME}-ut ${SRC_TEST})
target_link_libraries(${PROJECT_NAME}-ut ${PROJECT_NAME}-lib GTest::gtest_main GTest::gmock)

enable_testing()
add_test(NAME TestGroup COMMAND ${PROJECT_NAME}-ut)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}-ut)
