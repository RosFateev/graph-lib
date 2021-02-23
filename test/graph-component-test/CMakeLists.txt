#
# graph-component-test directory cmake file
#



# create a library
add_library(component-test OBJECT vertex-test.cc edge-test.cc)



# where to search for headers
target_include_directories(component-test PUBLIC ../../include
	                                             ../../lib/googletest-master/googletest/include)

