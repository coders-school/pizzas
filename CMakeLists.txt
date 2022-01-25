cmake_minimum_required(VERSION 3.11.0)

 set(CMAKE_CXX_STANDARD 17)
 set(CMAKE_CXX_STANDARD_REQUIRED ON)

 include(FetchContent)
 FetchContent_Declare(
   googletest
   GIT_REPOSITORY https://github.com/google/googletest.git
   GIT_TAG        main # release-1.10.0
 )
 # For Windows: Prevent overriding the parent project's compiler/linker settings
 set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
 FetchContent_MakeAvailable(googletest)

 # Now simply link against gtest or gtest_main as needed. Eg

 project(Pizzas)

 set(SRC_LIST
     src/Pizza.cpp
     src/Margherita.cpp
     src/Funghi.cpp
     src/Pizzeria.cpp
 )

 include_directories(src)
 add_library(${PROJECT_NAME}-lib ${SRC_LIST})
 add_executable(${PROJECT_NAME} src/main.cpp)
 target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib pthread)


 set(TEST_SRC_LIST
     test/PizzeriaTest.cpp
     test/test_main.cpp
 )

 link_libraries(gmock)
 add_executable(${PROJECT_NAME}-ut ${TEST_SRC_LIST})
 target_link_libraries(${PROJECT_NAME}-ut ${PROJECT_NAME}-lib)

 enable_testing()

 include(GoogleTest)
 gtest_discover_tests(${PROJECT_NAME}-ut)
