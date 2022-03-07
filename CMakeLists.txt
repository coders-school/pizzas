cmake_minimum_required(VERSION 3.11.0)

project(Pizzas 
        LANGUAGES CXX)

set(SRC_LIST
    src/Pizza.cpp
    src/Pizzeria.cpp
    src/Funghi.cpp
    src/Margherita.cpp)

# library target
add_library(${PROJECT_NAME}-lib STATIC ${SRC_LIST})
target_compile_options(${PROJECT_NAME}-lib 
                      PUBLIC -Wall -Wextra -pedantic -Wconversion)
target_compile_features(${PROJECT_NAME}-lib PUBLIC cxx_std_17)

# main app target
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}-lib)
target_compile_options(${PROJECT_NAME} 
                      PRIVATE -Wall -Wextra -pedantic -Wconversion)
target_compile_features(${PROJECT_NAME}-lib PRIVATE cxx_std_17)