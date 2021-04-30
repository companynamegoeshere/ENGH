project(engh_engine CXX)

project_source(engh_engine STATIC)

target_link_libraries(engh_engine)
target_link_libraries(engh_engine filament utils)
target_link_libraries(engh_engine glfw)
target_link_libraries(engh_engine glad)
target_link_libraries(engh_engine mathfu)
