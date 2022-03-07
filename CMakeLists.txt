cmake_minimum_required(VERSION 3.11.0)

project(Pizzas 
        LANGUAGES CXX)

# prepare Google Test
include(FetchContent)
FetchContent_Declare(
   googletest
   GIT_REPOSITORY https://github.com/google/googletest
   GIT_TAG main)
# For Windows: Prevent overriding the parent projec's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
set(SRC_LIST
    src/Pizza.cpp
    src/Pizzeria.cpp
    src/Funghi.cpp
    src/Margherita.cpp)

# test source files only
Set(TEST_SRC 
    test/test_main.cpp
    test/PizzeriaTest.cpp)

# library target
add_library(${PROJECT_NAME}-lib STATIC ${SRC_LIST})
target_compile_options(${PROJECT_NAME}-lib  PUBLIC -Wall -Wextra -pedantic -Wconversion)
target_compile_features(${PROJECT_NAME}-lib PUBLIC cxx_std_17)
target_include_directories(${PROJECT_NAME}-lib PUBLIC src/)

# main app target
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}-lib)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Wconversion)
target_compile_features(${PROJECT_NAME}-lib PRIVATE cxx_std_17)

# mock target
add_library(${PROJECT_NAME}-mocks INTERFACE)
target_link_libraries(${PROJECT_NAME}-mocks INTERFACE ${PROJECT_NAME}-lib)
target_compile_options(${PROJECT_NAME}-mocks INTERFACE -Wall -Wextra -pedantic -Wconversion)
target_compile_features(${PROJECT_NAME}-mocks INTERFACE cxx_std_17)
target_include_directories(${PROJECT_NAME}-mocks INTERFACE test/mocks)