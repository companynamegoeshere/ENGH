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

    SET(pathList "")
    IF (IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/public")
        LIST(APPEND pathList "${CMAKE_CURRENT_SOURCE_DIR}/public")
    ENDIF ()
    IF (pathList)
        include_directories(${pathList})
    ENDIF ()

    set("${name}_PATH" "${pathList}" PARENT_SCOPE)
    unset(pathList)

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
    IF (${BASE_NAME}_${other}_PATH)
        include_directories("${${BASE_NAME}_${other}_PATH}")
    ENDIF ()
ENDMACRO()

MACRO(include_raw_project name)
    target_link_libraries(${BASE_NAME}_${name} ${ARGN})
ENDMACRO()


add_subdirectory(engine)
add_subdirectory(editor)
add_subdirectory(test)
