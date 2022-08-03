add_library(lib Funghi.cpp  Funghi.hpp  Margherita.cpp  Margherita.hpp  Pizza.cpp  Pizza.hpp  Pizzeria.cpp  Pizzeria.hpp  main.cpp)
target_include_directories(lib PUBLIC .)

add_executable(pizzas_exe main.cpp)
target_link_libraries(pizzas_exe PRIVATE lib)
