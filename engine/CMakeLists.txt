project(engh_engine CXX)

project_source(engh_engine STATIC)

target_link_libraries(engh_engine)
target_link_libraries(engh_engine PUBLIC filament utils)
target_link_libraries(engh_engine PRIVATE glfw)
target_link_libraries(engh_engine PRIVATE glad)
target_link_libraries(engh_engine PUBLIC mathfu)
