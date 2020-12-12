#
# src directory cmake file
#



#
set(BINARY ${CMAKE_PROJECT_NAME})



# executable
add_executable(${BINARY} main.cc)



# access headers
target_include_directories(${BINARY} PUBLIC ../include)