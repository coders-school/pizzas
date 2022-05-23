cmake_minimum_required(VERSION 3.11.0)

# TODO: Write proper build system :)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SRC_LIST src/Funghi.cpp src/Margherita.cpp src/Pizza.cpp src/Pizzeria.cpp src/main.cpp)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

project(Pizzas)
enable_testing()

add_library(LIB STATIC src/Funghi.cpp src/Margherita.cpp src/Pizza.cpp src/Pizzeria.cpp)

add_executable(${PROJECT_NAME} src/main.cpp)
add_executable(${PROJECT_NAME}-ut test/PizzeriaTest.cpp test/test_main.cpp)

set(FLAGS -Wall -Wextra -Werror -Wpedantic - Wconversion -O3)

add_compile_options(LIB PRIVATE ${FLAGS})
add_compile_options(${PROJECT_NAME} PRIVATE ${FLAGS})
add_compile_options(${PROJECT_NAME}-ut PRIVATE ${FLAGS})

target_link_libraries(${PROJECT_NAME} ${LIB} pthred.h)
target_link_libraries(${PROJECT_NAME}-ut ${LIB})

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}-ut )