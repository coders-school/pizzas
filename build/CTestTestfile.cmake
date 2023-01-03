# CMake generated Testfile for 
# Source directory: /home/krzuch/pizzas
# Build directory: /home/krzuch/pizzas/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(PizzaTest "/home/krzuch/pizzas/build/Pizzas-test")
set_tests_properties(PizzaTest PROPERTIES  _BACKTRACE_TRIPLES "/home/krzuch/pizzas/CMakeLists.txt;48;add_test;/home/krzuch/pizzas/CMakeLists.txt;0;")
subdirs("_deps/googletest-build")
