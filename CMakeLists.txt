cmake_minimum_required(VERSION 3.9)

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")
include(cotire)

option(DEV "Development code (logs and asserts)" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DENGH_DEBUG")
IF (DEV)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DENGH_DEV")
ENDIF()
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(BASE_NAME "ENGH")
project(${BASE_NAME} CXX)

if (WIN32)
    set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif ()

MACRO(DllSetup PROJECT)
    if(WIN32)
        add_custom_command(TARGET ${PROJECT} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${PROJECT_SOURCE_DIR}/dlls"
                $<TARGET_FILE_DIR:${PROJECT_NAME}>)
    endif()
ENDMACRO()

FILE(GLOB children RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/third/*")
FOREACH(child ${children})
    add_subdirectory(${child})
ENDFOREACH()

add_subdirectory(engine)
add_subdirectory(editor)
add_subdirectory(test)
