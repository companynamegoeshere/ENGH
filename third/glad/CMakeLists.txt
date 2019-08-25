project(GLAD C)
set(subFolder "glad")
IF (CMAKE_BUILD_TYPE MATCHES DEBUG)
    set(subFolder "glad_debug")
ENDIF ()
add_library(glad STATIC
        ${subFolder}/src/gl.c
        ${subFolder}/include/glad/gl.h
        ${subFolder}/include/KHR/khrplatform.h
        )
target_include_directories(glad PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${subFolder}/include>"
        "$<INSTALL_INTERFACE:include>")
cotire(glad)
