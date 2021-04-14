cmake_minimum_required(VERSION 3.9)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

option(DEV "Development code (logs and asserts)" ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DENGH_DEBUG")

IF (CMAKE_BUILD_TYPE MATCHES DEBUG)
    SET(DEBUG ON CACHE BOOL "" FORCE)
ENDIF ()

IF (CMAKE_CXX_COMPILER MATCHES "clang")
    IF (DEBUG)
        string(APPEND CMAKE_CXX_FLAGS_DEBUG " -Wall -fno-omit-frame-pointer -fsanitize=address")
    ENDIF ()
ENDIF ()

IF (DEV)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DENGH_DEV")
ENDIF ()

set(BASE_NAME "ENGH")
project(${BASE_NAME} CXX)

if (WIN32)
    set(CMAKE_SHARED_LIBRARY_PREFIX "")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DWIN32")
endif ()

IF(MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
ENDIF()

MACRO(DllSetup PROJECT)
    IF (WIN32)
        add_custom_command(TARGET ${PROJECT} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${PROJECT_SOURCE_DIR}/dlls"
                $<TARGET_FILE_DIR:${PROJECT_NAME}>)
    ENDIF ()
ENDMACRO()

FUNCTION(project_source PROJECT type)
    file(GLOB_RECURSE source_files "private/*.cpp")
    IF (${type} STREQUAL "EXECUTABLE")
        add_executable(${PROJECT} ${source_files})
    ELSEIF (${type} STREQUAL "STATIC")
        add_library(${PROJECT} STATIC ${source_files})
    ELSEIF (${type} STREQUAL "SHARED")
        add_library(${PROJECT} SHARED ${source_files})
    ELSE ()
        message(FATAL_ERROR "Invalid type: ${type}. Expected EXECUTABLE, STATIC or SHARED")
    ENDIF ()

    set_target_properties(${PROJECT} PROPERTIES POSITION_INDEPENDENT_CODE ON)

    target_include_directories(${PROJECT} PUBLIC
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/public>"
            "$<INSTALL_INTERFACE:include>")
ENDFUNCTION()

add_subdirectory(third)

add_subdirectory(engine)
add_subdirectory(editor)
add_subdirectory(test)
