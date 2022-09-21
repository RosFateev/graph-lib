# resource managing cmake file


# copy resources
set(INNER_PATH "source/display/resources")
add_custom_command(
    OUTPUT "${CMAKE_BINARY_DIR}/${INNER_PATH}/Calibri-Regular.ttf"
    COMMAND "cp"
    ARGS "${PROJECT_SOURCE_DIR}/${INNER_PATH}/Calibri-Regular.ttf"
         "${CMAKE_BINARY_DIR}/${INNER_PATH}/Calibri-Regular.ttf"
    COMMENT "Copy resources to build directory")

add_custom_target(copy_resources ALL DEPENDS "${CMAKE_BINARY_DIR}/${INNER_PATH}/Calibri-Regular.ttf")
