cmake_minimum_required(VERSION 3.11.0)

# TODO: Write proper build system :)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SRC_LIST src/Funghi.cpp src/Margherita.cpp src/Pizza.cpp src/Pizzeria.cpp)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

project(Pizzas)
enable_testing()

add_library(LIB STATIC ${SRC_LIST})

add_executable(${PROJECT_NAME} src/main.cpp)
add_executable(${PROJECT_NAME}_UT test/PizzeriaTest.cpp)

target_link_libraries(${PROJECT_NAME} ${LIB} pthred.h)
target_link_libraries(${PROJECT_NAME}_UT ${LIB} gtest_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_UT)