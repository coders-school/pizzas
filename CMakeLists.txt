cmake_minimum_required(VERSION 3.11.0)

 project(Pizzas)
 set(BIN_EXE ${PROJECT_NAME})
 set(SRC_LIST src/Funghi.cpp src/Margherita.cpp src/Pizza.cpp src/Pizzeria.cpp)

 add_library(CUSTOM_STATIC_LIB STATIC ${SRC_LIST})

 add_executable(${BIN_EXE} src/main.cpp)
 find_package(Threads)
 target_link_libraries(${CUSTOM_STATIC_LIB} Threads::Threads)
 target_link_libraries(${BIN_EXE} PRIVATE CUSTOM_STATIC_LIB)
 target_compile_features(${BIN_EXE} PRIVATE cxx_std_17)
