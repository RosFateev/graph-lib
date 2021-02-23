#
# constructor-test directory cmake file
#



# create an object library
add_library(constructor-test OBJECT constructor.cc constructor.hpp)



# where to search for headers
target_include_directories(constructor-test PUBLIC ../../../lib/googletest-master/googletest/include
												   ../../../include)