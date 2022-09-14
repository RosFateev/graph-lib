# documentation cmake file


# process config file
configure_file(${PROJECT_SOURCE_DIR}/doc/Doxyfile.in
               ${CMAKE_BINARY_DIR}/doc/Doxyfile @ONLY)


# generate helper files
set(HELPER_FILES "${CMAKE_BINARY_DIR}/doc/header.html"
                 "${CMAKE_BINARY_DIR}/doc/footer.html"
                 "${CMAKE_BINARY_DIR}/doc/style.css")

add_custom_command(
    OUTPUT ${HELPER_FILES}
    COMMAND doxygen
    ARGS -w html ${HELPER_FILES} "${CMAKE_BINARY_DIR}/doc/Doxyfile"
    COMMENT "Generate support files for html documetnation")

add_custom_target(doc_helper_files ALL DEPENDS ${HELPER_FILES})


# generate documentation
add_custom_command(
    OUTPUT "${CMAKE_BINARY_DIR}/doc/html/index.html"
    COMMAND "doxygen"
    ARGS ${CMAKE_BINARY_DIR}/doc/Doxyfile
    COMMENT "Generate documentation")

add_custom_target(generate_doc ALL
    DEPENDS ${HELPER_FILES} 
            "${CMAKE_BINARY_DIR}/doc/html/index.html")
