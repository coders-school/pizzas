cmake_minimum_required(VERSION 3.11.0)
project(Pizzas)

set (SRC_LIST 
     src/Funghi.cpp 
     src/Margherita.cpp 
     src/Pizza.cpp 
     src/Pizzeria.cpp)
#set(FLAGS -Wall -Wextra -pedantic -Wconversion)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

find_library(PTHREAD_LIB pthread)

include_directories("${CMAKE_SOURCE_DIR}/src"
                    "${CMAKE_SOURCE_DIR}/test/mocks")

add_library(${PROJECT_NAME}_LIB STATIC ${SRC_LIST})
target_compile_options(${PROJECT_NAME}_LIB PRIVATE ${FLAGS})
target_compile_features(${PROJECT_NAME}_LIB PRIVATE cxx_std_17)

add_executable(${PROJECT_NAME} src/main.cpp)
target_compile_options(${PROJECT_NAME} PRIVATE ${FLAGS})
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_LIB ${PTHREAD_LIB})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

enable_testing()




# set(TEST_SRC_LIST test/PizzeriaTest.cpp)

# add tests sources as library
#add_library(XXX_LIB STATIC ${TEST_SRC_LIST})
#target_compile_options(XXX_LIB PRIVATE ${FLAGS})
#target_compile_features(XXX_LIB PRIVATE cxx_std_17)

add_executable(XXX test/PizzeriaTest.cpp)
target_link_libraries(XXX ${PROJECT_NAME}_LIB gtest gmock gtest_main)
target_compile_options(XXX PRIVATE ${FLAGS})
target_compile_features(XXX PRIVATE cxx_std_17)

include(GoogleTest)
gtest_discover_tests(XXX)
