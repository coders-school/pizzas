# CMake generated Testfile for 
# Source directory: /home/linux/workspace/pizzas
# Build directory: /home/linux/workspace/pizzas/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(PizzasTests "/home/linux/workspace/pizzas/build/Pizzas-ut")
set_tests_properties(PizzasTests PROPERTIES  _BACKTRACE_TRIPLES "/home/linux/workspace/pizzas/CMakeLists.txt;66;add_test;/home/linux/workspace/pizzas/CMakeLists.txt;0;")
subdirs("googletest-build")
