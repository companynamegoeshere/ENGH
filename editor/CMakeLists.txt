project(ENGH_EDITOR CXX)
add_executable(
        engh_editor
        main.cpp
)
target_link_libraries(engh_editor engh_core)
