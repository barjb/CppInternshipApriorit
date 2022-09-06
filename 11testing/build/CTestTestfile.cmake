# CMake generated Testfile for 
# Source directory: /home/jacob/Code/CPP/Apriorit/11testing
# Build directory: /home/jacob/Code/CPP/Apriorit/11testing/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[main_test]=] "main_test")
set_tests_properties([=[main_test]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/jacob/Code/CPP/Apriorit/11testing/CMakeLists.txt;21;add_test;/home/jacob/Code/CPP/Apriorit/11testing/CMakeLists.txt;0;")
add_test([=[tdd_task2]=] "main_test")
set_tests_properties([=[tdd_task2]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/jacob/Code/CPP/Apriorit/11testing/CMakeLists.txt;24;add_test;/home/jacob/Code/CPP/Apriorit/11testing/CMakeLists.txt;0;")
subdirs("googletest-main")
