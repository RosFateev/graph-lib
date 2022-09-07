# display cmake file


#
set(lib_name "display")


add_subdirectory(resources)


#
add_library(${lib_name} STATIC
    positioner.cpp
    drawer.cpp)
    #outputter.cpp)


target_link_libraries(${lib_name} PUBLIC
    component
    sfml-graphics
    sfml-window
    sfml-system)
target_include_directories(${lib_name} PUBLIC
    ${PROJECT_SOURCE_DIR}/../include)
