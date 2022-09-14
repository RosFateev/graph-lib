# implementation cmake file


#
set(lib_name "implementation")


#
add_library(${lib_name} STATIC)


target_link_libraries(${lib_name} PUBLIC
    component)
target_include_directories(${lib_name} PUBLIC
    ${PROJECT_SOURCE_DIR}/include)