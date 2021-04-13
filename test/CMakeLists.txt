project(ENGH_TEST CXX)
add_executable(
        engh_test
        main.cpp
        imgui_adapter.cpp imgui_impl_glfw.cpp
)

target_link_libraries(engh_test dear_imgui)
target_link_libraries(engh_test engh_engine)

set_property(TARGET engh_test PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
