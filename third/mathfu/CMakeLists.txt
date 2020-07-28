set(mathfu_build_benchmarks OFF CACHE BOOL "")
set(mathfu_build_tests OFF CACHE BOOL "")

add_subdirectory(mathfu)

add_library(mathfu INTERFACE)

target_include_directories(mathfu INTERFACE
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/mathfu/include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/mathfu/dependencies/vectorial/include>"
        "$<INSTALL_INTERFACE:include>")
