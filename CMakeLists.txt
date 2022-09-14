# root cmake file


# project name
project(graph-lib)


# requirements
cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)


#
add_subdirectory(doc)
add_subdirectory(source)


# define executable
#add_executable(${PROJECT_NAME} source/main.cpp)
add_library(${PROJECT_NAME} source/main.cpp)


# specify c++ version
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)


# manage dependencies
target_link_libraries(${PROJECT_NAME} PUBLIC
    component
    display)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/include)
