# resource managing cmake file


# copy resources
add_custom_command(
    OUTPUT "${CMAKE_BINARY_DIR}/resources/"
    COMMAND "cp"
    ARGS "-r"
         "${PROJECT_SOURCE_DIR}/display/resources/"
         "${CMAKE_BINARY_DIR}/"
    COMMENT "Copy resources to build directory")

add_custom_target(copy_resources ALL DEPENDS "${CMAKE_BINARY_DIR}/resources/")
