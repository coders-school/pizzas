 cmake_minimum_required(VERSION 3.11.0)

 project(pizzas)

 add_library(lib src/Funghi.cpp
                 src/Funghi.hpp
                 src/Margherita.cpp
                 src/Margherita.hpp
                 src/Pizza.cpp
                 src/Pizza.hpp
                 src/Pizzeria.cpp
                 src/Pizzeria.hpp
                 )

 target_include_directories(lib PUBLIC /src)

 add_executable(pizzas_exe src/main.cpp)
 target_link_libraries(pizzas_exe PRIVATE lib)
