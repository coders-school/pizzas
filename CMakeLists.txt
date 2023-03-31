cmake_minimum_required(VERSION 3.16.0)
project(Pizzas)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(SRC_LIST
    src/Funghi.cpp
    src/Margherita.cpp
    src/Pizza.cpp
    src/Pizzeria.cpp)

set(FLAGS -Wall -Wextra -Werror -pedantic -Wconversion -O1)


add_library(${PROJECT_NAME}-lib STATIC ${SRC_LIST})
target_compile_options(${PROJECT_NAME}-lib PRIVATE ${FLAGS})
target_compile_features(${PROJECT_NAME}-lib PRIVATE cxx_std_17)

add_executable(${PROJECT_NAME} src/main.cpp)
target_compile_options(${PROJECT_NAME} PRIVATE ${FLAGS})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib)


enable_testing()
link_libraries(gmock)
add_test(NAME pizzasTests COMMAND ${PROJECT_NAME}-ut)
# TODO: Write proper build system :)

add_executable(${PROJECT_NAME}-ut test/test_main.cpp test/PizzeriaTest.cpp)
target_link_libraries(${PROJECT_NAME}-ut ${PROJECT_NAME}-lib)
target_compile_features(${PROJECT_NAME}-ut PRIVATE cxx_std_17)
target_compile_options(${PROJECT_NAME}-ut PRIVATE ${FLAGS})

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}-ut)
