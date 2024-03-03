cmake_minimum_required(VERSION 3.11.0)
project(Pizzas)
set(CMAKE_CXX_STANDARD 17)
set (SRC_LIST src/Funghi.cpp  src/Margherita.cpp src/Pizza.cpp src/Pizzeria.cpp)
#set(FLAGS -Wall -Wextra -Werror -pedantic -Wconversion)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

find_library(PTHREAD_LIB pthread)

include_directories("${CMAKE_SOURCE_DIR}/src"
                    "${CMAKE_SOURCE_DIR}/test/mocks")

add_library(${PROJECT_NAME}-lib STATIC ${SRC_LIST})
target_compile_options(${PROJECT_NAME}-lib PRIVATE ${FLAGS})


add_executable(${PROJECT_NAME} src/main.cpp)
target_compile_options(${PROJECT_NAME} PRIVATE ${FLAGS})
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib)

enable_testing()

add_executable( PT test/PizzeriaTest.cpp)
target_link_libraries(
  PT
  GTest::gtest_main
  gtest gmock
  ${PROJECT_NAME}-lib 
  
)

include(GoogleTest)
gtest_discover_tests(PT)
