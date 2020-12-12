#
# root directory cmake file
#



# some requirements
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)



# setting project's name 
project(graph-lib)



# adding necessary subdirectories
add_subdirectory(src)
add_subdirectory(lib/googletest-master)
add_subdirectory(test)



# untested (!!!)

#set(LIBRARY_NAME graph_lib)

#target_include_directories(${LIBRARY_NAME} PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${LIBRARY_NAME}>
#                                                   $<INSTALL_INTERFACE:include/${LIBRARY_NAME}>
#)
#target_include_directories(${LIBRARY_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#                                                  $<INSTALL_INTERFACE:include>
#)