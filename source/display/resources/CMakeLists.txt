# resource managing cmake file


# copy resources
add_custom_command(
    OUTPUT "${CMAKE_BINARY_DIR}/graph-lib/source/display/resources/Calibri-Regular.ttf"
    COMMAND "cp"
    ARGS "${PROJECT_SOURCE_DIR}/source/display/resources/Calibri-Regular.ttf"
         "${CMAKE_BINARY_DIR}/graph-lib/source/display/resources/Calibri-Regular.ttf"
    COMMENT "Copy resources to build directory")

add_custom_target(copy_resources ALL DEPENDS "${CMAKE_BINARY_DIR}/graph-lib/source/display/resources/Calibri-Regular.ttf")
