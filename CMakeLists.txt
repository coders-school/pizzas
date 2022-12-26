cmake_minimum_required(VERSION 3.14)

# TODO: Write proper build system :)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

project(Pizzas)
enable_testing()

set(SRC_LIST
    src/Funghi.cpp
    src/Margherita.cpp
    src/Pizza.cpp
    src/Pizzeria.cpp)

set (FLAGS -Wall -Wextra -Werror -Wpedantic -Wconversion -O3)

add_library(${PROJECT_NAME}-lib STATIC ${SRC_LIST})
add_executable(${PROJECT_NAME} src/main.cpp)
add_executable(${PROJECT_NAME}-ut test/test_main.cpp test/PizzeriaTest.cpp)

target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib pthread)
target_link_libraries(${PROJECT_NAME}-ut gtest_main gmock ${PROJECT_NAME}-lib)

target_compile_options(${PROJECT_NAME}-lib PRIVATE ${FLAGS})
target_compile_options(${PROJECT_NAME} PRIVATE ${FLAGS})
target_compile_options(${PROJECT_NAME}-ut PRIVATE ${FLAGS})

# add_test(NAME someTests COMMAND ${PROJECT_NAME}-ut)
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}-ut)
