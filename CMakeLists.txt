cmake_minimum_required(VERSION 3.11.0)

# TODO: Write proper build system :)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SRC_LIST src/Funghi.cpp src/Margherita.cpp src/Pizza.cpp src/Pizzeria.cpp)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        main # release-1.10.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

project(Pizzas)
enable_testing()

add_library(LIB STATIC ${SRC_LIST})

add_executable(${PROJECT_NAME} src/main.cpp)
add_executable(${PROJECT_NAME}_UT test/PizzeriaTest.cpp)

target_link_libraries(${PROJECT_NAME} ${LIB})
target_link_libraries(${PROJECT_NAME} pthread)
target_link_libraries(${PROJECT_NAME}_UT ${LIB})
target_link_libraries(${PROJECT_NAME}_UT gtest_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_UT)
add_test(NAME someTests COMMAND ${PROJECT_NAME}-ut)
