# implementation cmake file


#
set(lib_name "implementation")


#
add_library(${lib_name} PUBLIC
    adjacency-list.cpp
    incidence-matrix.cpp)
