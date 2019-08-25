project(DEAR_IMGUI CXX)
add_library(
        dear_imgui STATIC
        imgui/imgui.cpp
)

set_target_properties(dear_imgui
        PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_include_directories(dear_imgui PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
        "$<INSTALL_INTERFACE:include>")

target_link_libraries(dear_imgui)
cotire(dear_imgui)
