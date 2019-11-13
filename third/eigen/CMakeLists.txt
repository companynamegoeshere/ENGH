project(Eigen3 CXX)
add_library(Eigen3 INTERFACE)

target_include_directories(Eigen3 INTERFACE
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
        "$<INSTALL_INTERFACE:include>")

target_link_libraries(Eigen3)
cotire(Eigen3)
