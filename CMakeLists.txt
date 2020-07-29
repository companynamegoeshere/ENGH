cmake_minimum_required(VERSION 3.9)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
#set(CMAKE_UNITY_BUILD TRUE)

option(DEV "Development code (logs and asserts)" ON)

set(CMAKE_CXX_STANDARD 17)

FUNCTION(SetupEngineFlags)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DENGH_DEBUG")

    IF (CMAKE_BUILD_TYPE MATCHES DEBUG)
        SET(DEBUG ON CACHE BOOL "" FORCE)
    ENDIF (CMAKE_BUILD_TYPE MATCHES DEBUG)

    IF (MSVC)
        set(CompilerFlags
                CMAKE_CXX_FLAGS
                CMAKE_CXX_FLAGS_DEBUG
                CMAKE_CXX_FLAGS_RELEASE
                CMAKE_C_FLAGS
                CMAKE_C_FLAGS_DEBUG
                CMAKE_C_FLAGS_RELEASE
                )
        foreach (CompilerFlag ${CompilerFlags})
            IF ("${${CompilerFlag}}" MATCHES "/MTd")
                STRING(REPLACE "/MTd" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
            ELSEIF ("${${CompilerFlag}}" MATCHES "/MDd")
                STRING(REPLACE "/MDd" "/MD" ${CompilerFlag} "${${CompilerFlag}}")
            ELSE ()
                STRING(APPEND ${CompilerFlag} " /MD")
            ENDIF ()
        endforeach ()
    ENDIF ()

    IF (CMAKE_CXX_COMPILER MATCHES "clang")
        IF (DEBUG)
            string(APPEND CMAKE_CXX_FLAGS_DEBUG " -Wall -fno-omit-frame-pointer -fsanitize=address")
        ENDIF ()
    ENDIF ()

    IF (DEV)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DENGH_DEV")
    ENDIF ()
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
ENDFUNCTION()

set(BASE_NAME "ENGH")
project(${BASE_NAME} CXX)

if (WIN32)
    set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif ()

MACRO(DllSetup PROJECT)
    IF (WIN32)
        add_custom_command(TARGET ${PROJECT} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${PROJECT_SOURCE_DIR}/dlls"
                $<TARGET_FILE_DIR:${PROJECT_NAME}>)
    ENDIF ()
ENDMACRO()

FILE(GLOB children RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/third/*")
FOREACH (child ${children})
    add_subdirectory(${child})
ENDFOREACH ()

add_subdirectory(engine)
add_subdirectory(editor)
add_subdirectory(test)
