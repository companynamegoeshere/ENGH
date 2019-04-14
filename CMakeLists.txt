cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DENGH_DEBUG")
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(BASE_NAME "ENGH")
project(${BASE_NAME} CXX)

MACRO(create_project _name type)
    set(name "${BASE_NAME}_${_name}")
    project("${name}" CXX)

    set(src ${ARGN})

	include_directories(${CMAKE_CURRENT_SOURCE_DIR})

	set("${name}_PATH" "${CMAKE_CURRENT_SOURCE_DIR}" PARENT_SCOPE)

    if ("${type}" STREQUAL "SHARED")
        add_library("${name}" SHARED ${src})
    elseif ("${type}" STREQUAL "EXECUTABLE")
        add_executable("${name}" ${src})
    else ()
        message(FATAL_ERROR "create_project supports only LIBRARY and EXECUTABLE")
    endif ()

    set_target_properties("${name}" PROPERTIES LINKER_LANGUAGE CXX)
    unset(src)
    unset(name)
ENDMACRO()

MACRO(include_project name other)
    target_link_libraries(${BASE_NAME}_${name} ${BASE_NAME}_${other})
	include_directories("${${BASE_NAME}_${other}_PATH}")
ENDMACRO()

MACRO(include_raw_project name other)
    target_link_libraries(${name} ${other})
ENDMACRO()

MACRO(subproject name)
	add_subdirectory(${name})
ENDMACRO()

subproject(core)
subproject(test)

