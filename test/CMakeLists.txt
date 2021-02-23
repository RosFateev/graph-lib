#
# test directory cmake file
#



# 
set(BINARY ${CMAKE_PROJECT_NAME}_test)



#
add_subdirectory(graph-component-test)
add_subdirectory(graph-implementation-test)
add_subdirectory(graph-component-support-test)



# create executable; reference necessary object libraries
add_executable(${BINARY} main.cc
	                     $<TARGET_OBJECTS:component-test>
	                     $<TARGET_OBJECTS:implementation-test>
	                     $<TARGET_OBJECTS:component-support-test>)



add_test(NAME ${BINARY} COMMAND ${BINARY})



target_link_libraries(${BINARY} PUBLIC 	gtest)

target_include_directories(${BINARY} PUBLIC ../lib/googletest-master/googletest/include)