project(DEAR_IMGUI CXX)
add_library(
        dear_imgui STATIC
        imgui/imgui.h
        imgui/imgui.cpp
        imgui/imgui_widgets.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_demo.cpp
)

set_target_properties(dear_imgui
        PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_compile_options(dear_imgui PRIVATE -w)

target_include_directories(dear_imgui PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
        "$<INSTALL_INTERFACE:include>")

target_link_libraries(dear_imgui)
