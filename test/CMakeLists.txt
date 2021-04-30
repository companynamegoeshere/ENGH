project(ENGH_TEST CXX)
add_executable(
        engh_test
        main.cpp
        imgui_adapter.cpp imgui_impl_glfw.cpp
)

target_link_libraries(engh_test PUBLIC dear_imgui)
target_link_libraries(engh_test PUBLIC engh_engine)

set_property(TARGET engh_test PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)
set(GENERATION_ROOT ${CMAKE_CURRENT_BINARY_DIR})
set(RESOURCE_DIR  "${GENERATION_ROOT}/generated/resources")
set(MATERIAL_DIR  "${GENERATION_ROOT}/generated/material")
set(TEXTURE_DIR "${GENERATION_ROOT}/generated/texture")
set(RESOURCE_BINS)

file(GLOB_RECURSE MATERIAL_SRCS "materials/*.mat")

file(MAKE_DIRECTORY ${MATERIAL_DIR})

foreach (mat_src ${MATERIAL_SRCS})
    get_filename_component(localname "${mat_src}" NAME_WE)
    get_filename_component(fullname "${mat_src}" ABSOLUTE)
    set(output_path "${MATERIAL_DIR}/${localname}.filamat")
    add_custom_command(
            OUTPUT ${output_path}
            COMMAND matc ${MATC_BASE_FLAGS} -o ${output_path} ${fullname}
            MAIN_DEPENDENCY ${mat_src}
            DEPENDS matc
            COMMENT "Compiling material ${mat_src} to ${output_path}"
    )
    list(APPEND RESOURCE_BINS ${output_path})
endforeach ()

file(MAKE_DIRECTORY ${RESOURCE_DIR})

get_resgen_vars(${RESOURCE_DIR} resources)

add_custom_command(
        OUTPUT ${RESGEN_OUTPUTS}
        COMMAND resgen ${RESGEN_FLAGS} ${RESOURCE_BINS}
        DEPENDS resgen ${RESOURCE_BINS}
        COMMENT "Aggregating resources"
)

if (DEFINED RESGEN_SOURCE_FLAGS)
    set_source_files_properties(${RESGEN_SOURCE} PROPERTIES COMPILE_FLAGS ${RESGEN_SOURCE_FLAGS})
endif()

# CMake fails to invoke ar on Windows unless there is at least one C/C++ file in the library.
set(DUMMY_SRC "${RESOURCE_DIR}/dummy.c")
add_custom_command(OUTPUT ${DUMMY_SRC} COMMAND echo "//" > ${DUMMY_SRC})

project(sample-resources C)
add_library(sample-resources ${DUMMY_SRC} ${RESGEN_SOURCE})
target_include_directories(engh_test PRIVATE ${GENERATION_ROOT})
target_link_libraries(engh_test PRIVATE sample-resources)
