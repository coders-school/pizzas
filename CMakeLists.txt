cmake_minimum_required(VERSION 3.11.0)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        main
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)

set(SRC_LIST 
    src/Funghi.cpp 
    src/Margherita.cpp 
    src/Pizza.cpp 
    src/Pizzeria.cpp
)

include_directories(src)

project(Pizzas)

enable_testing()

add_executable(${PROJECT_NAME} src/main.cpp)

add_library(${PROJECT_NAME}-lib STATIC ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib -lpthread)

# set(SRC_TEST_LIST 
#     test/PizzeriaTest.cpp
#     test/test_main.cpp
# )



add_executable(${PROJECT_NAME}-test test/PizzeriaTest.cpp test/test_main.cpp)

target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME}-lib gtest gmock)

enable_testing()

add_test(NAME PizzaTest COMMAND ${PROJECT_NAME}-test)