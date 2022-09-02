# source root cmake file


project(graph-lib)


cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)


add_subdirectory(component)
add_subdirectory(display)
#add_subdirectory(implementation)


add_executable(${PROJECT_NAME} main.cpp)
#add_library(${PROJECT_NAME})


set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)


target_link_libraries(${PROJECT_NAME} PUBLIC
    component
    display)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/../include)