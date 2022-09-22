# runner cmake file


# project name
project(runner LANGUAGES CXX)


# make sure cmake is not outdated
cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)


# build graph-lib together
add_subdirectory(graph-lib)


# create executable
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/runner.cpp
    src/fetcher.cpp)


# relatively modern c++
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)


# headers locations
target_include_directories(${PROJECT_NAME} PUBLIC
    "${PROJECT_SOURCE_DIR}/graph-lib/include"
    "${PROJECT_SOURCE_DIR}/include")


# libs locations
target_link_libraries(${PROJECT_NAME} PUBLIC
    graph-lib)