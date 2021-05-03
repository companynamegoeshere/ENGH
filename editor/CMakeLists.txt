project(ENGH_EDITOR CXX)

project_source(engh_editor EXECUTABLE)
target_link_libraries(engh_editor PUBLIC engh_engine)
#target_link_libraries(engh_editor PUBLIC dear_imgui)
target_link_libraries(engh_editor PUBLIC imgui filagui)

add_custom_command(TARGET engh_editor POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets
        ${CMAKE_CURRENT_BINARY_DIR}/assets)
