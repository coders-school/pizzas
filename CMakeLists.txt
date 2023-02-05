cmake_minimum_required(VERSION 3.11.0)
project(Pizzas)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(SRC_LIST_MAIN src/Pizza.cpp src/Pizzeria.cpp src/Margherita.cpp src/Funghi.cpp)

set(SRC_LIST_TEST test/PizzeriaTest.cpp test/test_main.cpp)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)

add_library(${PROJECT_NAME}-lib STATIC ${SRC_LIST_MAIN})
target_compile_features(${PROJECT_NAME}-lib PRIVATE cxx_std_17)

add_executable(${PROJECT_NAME} src/main.cpp)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib)

add_executable(${PROJECT_NAME}-ut ${SRC_LIST_TEST})
target_compile_features(${PROJECT_NAME}-ut PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME}-ut ${PROJECT_NAME}-lib)

enable_testing()
add_test(NAME PizzeriaTests COMMAND ${PROJECT_NAME}-ut)

