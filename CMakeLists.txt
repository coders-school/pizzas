cmake_minimum_required(VERSION 3.11.0)
project(Pizzas C CXX)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

# Now simply link against gtest or gtest_main as needed. Eg

enable_testing()

set(SRC_LIST src/Funghi.cpp src/Margherita.cpp src/Pizza.cpp src/Pizzeria.cpp)
set(FLAGS -Wextra -Werror -pedantic -Wconversion -O3)

include_directories(src)
include_directories(test)

add_library(${PROJECT_NAME}-lib STATIC ${SRC_LIST})
target_compile_options(${PROJECT_NAME}-lib PRIVATE ${FLAGS})
target_compile_features(${PROJECT_NAME}-lib PRIVATE cxx_std_17)

add_executable(${PROJECT_NAME}-main src/main.cpp)
target_compile_options(${PROJECT_NAME}-main PRIVATE ${FLAGS})
target_compile_features(${PROJECT_NAME}-main PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME}-main ${PROJECT_NAME}-lib Threads::Threads)

add_executable(${PROJECT_NAME}-test test/test_main.cpp test/PizzeriaTest.cpp)
target_compile_options(${PROJECT_NAME}-test PRIVATE ${FLAGS})
target_compile_features(${PROJECT_NAME}-test PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME}-lib gtest_main gmock Threads::Threads)

add_test(NAME PizzasTests COMMAND ${PROJECT_NAME}-test)
