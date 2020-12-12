#
# graph-component-test directory cmake file
#



# create a library
add_library(component-test OBJECT vertex-test.cc edge-test.cc)



# link libraries
target_link_libraries(component-test PUBLIC gtest)

# where to search for headers
target_include_directories(component-test PUBLIC ../../include
	                                             ../../lib/googletest-master/googletest/include)

