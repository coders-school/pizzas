cmake_minimum_required(VERSION 3.11.0)


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

project(Pizzas)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SRC_LIST src/Funghi.cpp src/Margherita.cpp src/Pizza.cpp src/Pizzeria.cpp)

add_library(${PROJECT_NAME}-lib STATIC ${SRC_LIST})


add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}-lib pthread)

enable_testing()

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME}-ut test/PizzeriaTest.cpp)
target_include_directories(${PROJECT_NAME}-ut PRIVATE src)
target_link_libraries(${PROJECT_NAME}-ut PRIVATE GTest::gtest_main gmock ${PROJECT_NAME}-lib)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}-ut)







