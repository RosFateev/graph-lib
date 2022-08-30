# component cmake file


#
set(lib_name "component")


#
add_library(${lib_name} STATIC
    edge.cpp
    vertex-support.cpp)


target_include_directories(${lib_name} PUBLIC
    ${PROJECT_SOURCE_DIR}/../include)
