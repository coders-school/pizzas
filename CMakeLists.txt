cmake_minimum_required(VERSION 3.11.0)

set(PROJECT_NAME Pizzas)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(FILE_LIST_SRC
    src/Funghi.cpp 
    src/Margherita.cpp 
    src/Pizza.cpp 
    src/Pizzeria.cpp)
set(FILE_LIST_TEST
    test/PizzeriaTest.cpp 
    test/test_main.cpp)

include_directories(src)
include_directories(test)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)

add_library(${PROJECT_NAME}-lib STATIC ${FILE_LIST_SRC})
add_executable(${PROJECT_NAME} src/main.cpp)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -lphtread)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib)

link_libraries(gmock)
add_executable(${PROJECT_NAME}-ut ${FILE_LIST_TEST})
target_compile_options(${PROJECT_NAME}-ut PRIVATE -Wall -Wextra -pedantic -lphtread)
target_link_libraries(${PROJECT_NAME}-ut ${PROJECT_NAME}-lib)

enable_testing()
add_test(NAME PizzaTests COMMAND ${PROJECT_NAME}-ut)
