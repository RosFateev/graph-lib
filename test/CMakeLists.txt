#
# test directory cmake file
#



# 
set(BINARY ${CMAKE_PROJECT_NAME}_test)



#
add_subdirectory(graph-component-test)



# create executable
add_executable(${BINARY} main.cc
	                     $<TARGET_OBJECTS:component-test>)


add_test(NAME ${BINARY} COMMAND ${BINARY})


target_link_libraries(${BINARY} PUBLIC gtest)

target_include_directories(${BINARY} PUBLIC ../lib/googletest-master/googletest/include)