#
# graph-implementation-test directory cmake file
#



# create a library
add_library(implementation-test OBJECT adjacency-list-test.cc manager-test.cc)



# where to search for headers
target_include_directories(implementation-test PUBLIC 	../../include
	                                             		../../lib/googletest-master/googletest/include)

