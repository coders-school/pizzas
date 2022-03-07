cmake_minimum_required(VERSION 3.11.0)

project(Pizzas 
        LANGUAGES CXX)

# common source files
set(SRC_LIST src/Pizza.cpp src/Pizzeria.cpp src/Funghi.cpp src/Margherita.cpp)

# test source files only
set(TEST_SRC test/test_main.cpp test/PizzeriaTest.cpp)

# library target
add_library(${PROJECT_NAME}-lib STATIC ${SRC_LIST})
target_compile_options(${PROJECT_NAME}-lib  PUBLIC -Wall -Wextra -pedantic -Wconversion)
target_compile_features(${PROJECT_NAME}-lib PUBLIC cxx_std_17)
target_include_directories(${PROJECT_NAME}-lib PUBLIC src/)

# main app target
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}-lib pthread)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Wconversion)
target_compile_features(${PROJECT_NAME}-lib PRIVATE cxx_std_17)

# mock target
add_library(${PROJECT_NAME}-mocks INTERFACE)
target_link_libraries(${PROJECT_NAME}-mocks INTERFACE ${PROJECT_NAME}-lib)
target_compile_options(${PROJECT_NAME}-mocks INTERFACE -Wall -Wextra -pedantic -Wconversion)
target_compile_features(${PROJECT_NAME}-mocks INTERFACE cxx_std_17)
target_include_directories(${PROJECT_NAME}-mocks INTERFACE test/mocks)

# test target
add_executable(${PROJECT_NAME}-ut ${TEST_SRC})
target_link_libraries(${PROJECT_NAME}-ut
                      ${PROJECT_NAME}-lib 
                      ${PROJECT_NAME}-mocks
                      gtest_main 
                      gmock_main)
target_compile_options(${PROJECT_NAME}-ut PRIVATE -Wall -Wextra -pedantic)
target_compile_features(${PROJECT_NAME}-ut PRIVATE cxx_std_17)

# prepare Google Test
include(FetchContent)
FetchContent_Declare(
   googletest
   GIT_REPOSITORY https://github.com/google/googletest
   GIT_TAG main)

FetchContent_MakeAvailable(googletest)

# enable testing
enable_testing()
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}-ut)