# Test cmake file


# 
set(test_project "test")


# add tests
add_subdirectory(manual)
add_subdirectory(component)
add_subdirectory(implementation)
add_subdirectory(algorithm)


# create executable; reference necessary object libraries
add_executable(${BINARY} main.cc
	                     $<TARGET_OBJECTS:component-test>)
	                     #$<TARGET_OBJECTS:implementation-test>)
	                     #$<TARGET_OBJECTS:component-support-test>)



add_test(NAME ${BINARY} COMMAND ${BINARY})



target_link_libraries(${BINARY} PUBLIC 	gtest)

target_include_directories(${BINARY} PUBLIC ../lib/googletest-master/googletest/include)