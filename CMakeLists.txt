cmake_minimum_required(VERSION 3.11.0)
project(Pizzas)

include(FetchContent)
 FetchContent_Declare(
   googletest
   GIT_REPOSITORY https://github.com/google/googletest.git
   GIT_TAG        main
 )
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(SRC_LIST
        src/Pizza.cpp
        src/Funghi.cpp
        src/Margherita.cpp
        src/Pizzeria.cpp
    )
# add directory for include files
include_directories(src)
# create project library    
add_library(${PROJECT_NAME}-lib STATIC ${SRC_LIST})

# create executable
add_executable(${PROJECT_NAME} src/main.cpp)

# link library
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib pthread)

# set C++17 standart
set_target_properties(${PROJECT_NAME} PROPERTIES
                       CXX_STANDARD 17
                       CMAKE_CXX_STANDARD_REQUIRED ON)  

# TESTS
set(TEST_SRC_LIST
        test/PizzeriaTest.cpp  
        test/test_main.cpp 
    )
    
# create executable
add_executable(${PROJECT_NAME}-ut ${TEST_SRC_LIST})   

# link library
target_link_libraries(${PROJECT_NAME}-ut ${PROJECT_NAME}-lib gtest gmock)  

# set C++17 standart
set_target_properties(${PROJECT_NAME}-ut PROPERTIES
                       CXX_STANDARD 17
                       CMAKE_CXX_STANDARD_REQUIRED ON)  

# TODO: Write proper build system :)
