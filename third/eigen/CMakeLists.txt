project(Eigen3 CXX)
add_library(
        Eigen3 STATIC
        eigen/Eigen/Eigen
)

set_target_properties(Eigen3 PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(Eigen3
        PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_include_directories(Eigen3 PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/Eigen"
        "$<INSTALL_INTERFACE:include>")

target_link_libraries(Eigen3)
cotire(Eigen3)
