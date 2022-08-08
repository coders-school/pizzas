cmake_minimum_required(VERSION 3.11.0)

project(Pizzas)
set(SRC_LIST
    src/Funghi.cpp
    src/Margherita.cpp
    src/Pizza.cpp
    src/Pizzeria.cpp
)

SET(TEST_SRC_LIST
    test/PizzeriaTest.cpp
    test/test_main.cpp
)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(src)
add_library(CUSTOM_STATIC_LIB STATIC ${SRC_LIST})

add_executable(${PROJECT_NAME} src/main.cpp)
find_package(Threads)
target_link_libraries(${CUSTON_STATIC_LIB} Threads::Threads)
target_link_libraries(${PROJECT_NAME} PRIVATE CUSTOM_STATIC_LIB)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

#message(FATAL_ERROR "Build step AFTER binary failed")

#create test binary
link_libraries(gmock)
add_executable(${PROJECT_NAME}-ut ${TEST_SRC_LIST})
#linking gtest library to test binary
target_link_libraries(${PROJECT_NAME}-ut CUSTOM_STATIC_LIB)

enable_testing()

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}-ut)

