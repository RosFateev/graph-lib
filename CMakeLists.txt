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
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)



include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )



target_link_libraries(graph-lib ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )